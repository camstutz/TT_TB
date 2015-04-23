/*!
 * @file trigger_tower.cpp
 * @author Christian Amstutz
 * @date April 23, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower.hpp"

// *****************************************************************************

const unsigned int trigger_tower::detector_layer_nr = NR_DETECTOR_LAYERS;
const unsigned int trigger_tower::prb_nr = NR_PRB_PER_TRIGGER_TOWER;
const unsigned int trigger_tower::dtc_per_prb = NR_DTC_PER_PRB;
const unsigned int trigger_tower::AM_boards_per_proc_unit = NR_AM_BOARDS;

// *****************************************************************************
trigger_tower::trigger_tower(const sc_module_name _name) :
        sc_module(_name),
        clk("clk"),
        dtc_inputs(prb_nr, dtc_per_prb, "dtc_input"),
        hit_outputs(prb_nr * AM_boards_per_proc_unit, detector_layer_nr, "hit_output"),
        trigger_tower_interconnect(prb_nr, prb_nr, "trigger_tower_interconnect"),
        am_board_in_sig(prb_nr, AM_boards_per_proc_unit, detector_layer_nr, "am_board_sig"),
        dataOrganizers(prb_nr, "dataOrganizer"),
        //processorOrganizers(prb_nr, "processorOrganizer"),
        amBoards(prb_nr, AM_boards_per_proc_unit, "AM_Board")
{
    unsigned int do_nr = 0;
    sc_map_linear<data_organizer>::iterator data_organizer_it = dataOrganizers.begin();
    for (; data_organizer_it != dataOrganizers.end(); ++data_organizer_it)
    {
        data_organizer_it->clk.bind(clk);
        sc_map_square<sc_in<data_organizer::dtc_input_t> >::square_iterator
                dtc_input_it = dtc_inputs.begin_partial(do_nr, false, 0, true);
        data_organizer_it->dtc_inputs.bind_by_iter(dtc_input_it);
        sc_map_square<sc_buffer<data_organizer::proc_unit_output_t > >::square_iterator
                intercon_it = trigger_tower_interconnect.begin_partial(do_nr, false, 0, true);
        data_organizer_it->proc_unit_outputs.bind_by_iter(intercon_it);

        ++do_nr;
    }

    for (unsigned int po_id=0; po_id < prb_nr; ++po_id)
    {
        std::stringstream po_name;
        po_name << "processorOrganizer_" << po_id;
        processorOrganizers[po_id] = new processor_organizer(po_name.str().c_str(), po_id);
        processorOrganizers[po_id]->clk.bind(clk);
        sc_map_square<sc_buffer<data_organizer::proc_unit_output_t > >::square_iterator
                intercon_it = trigger_tower_interconnect.begin_partial(0, true, po_id, false);
        processorOrganizers[po_id]->do_inputs.bind_by_iter(intercon_it);
        sc_map_cube<sc_buffer<processor_organizer::processor_output_t> >::cube_iterator
                am_board_it = am_board_in_sig.begin_partial(po_id, false, 0, true, 0, true);
        processorOrganizers[po_id]->processor_outputs.bind_by_iter(am_board_it);
    }

//    unsigned int po_nr = 0;
//    sc_map_linear<processor_organizer>::iterator processor_organizer_it = processorOrganizers.begin();
//    for (; processor_organizer_it != processorOrganizers.end(); ++processor_organizer_it)
//    {
//        processor_organizer_it->clk.bind(clk);
//        sc_map_square<sc_buffer<data_organizer::proc_unit_output_t > >::square_iterator
//                intercon_it = trigger_tower_interconnect.begin_partial(0, true, po_nr, false);
//        processor_organizer_it->do_inputs.bind_by_iter(intercon_it);
//        sc_map_cube<sc_buffer<processor_organizer::processor_output_t> >::cube_iterator
//                am_board_it = am_board_in_sig.begin_partial(po_nr, false, 0, true, 0, true);
//        processor_organizer_it->processor_outputs.bind_by_iter(am_board_it);
//
//        ++po_nr;
//    }

    sc_map_square<am_board>::iterator am_board_it = amBoards.begin();
    unsigned int am_board_id = 0;
    for (; am_board_it != amBoards.end(); ++am_board_it)
    {
        sc_map_square<am_board>::full_key_type am_board_key = amBoards.get_key(*am_board_it).second;

        am_board_it->clk.bind(clk);
        sc_map_cube<sc_buffer<processor_organizer::processor_output_t> >::cube_iterator
                input_it = am_board_in_sig.begin_partial(am_board_key.Y_dim, false, am_board_key.X_dim, false, 0, true);
        am_board_it->frame_inputs.bind_by_iter(input_it);
        sc_map_square<sc_out<am_board::output_stream_t> >::square_iterator
                hit_output_it = hit_outputs.begin_partial(am_board_id, false, 0, true);
        am_board_it->hit_output.bind_by_iter(hit_output_it);

        ++am_board_id;
    }

	return;
}
