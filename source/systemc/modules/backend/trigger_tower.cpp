/*!
 * @file trigger_tower.cpp
 * @author Christian Amstutz
 * @date May 5, 2015
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
        data_organizer_it->dtc_inputs.bind(dtc_inputs(do_nr, do_nr, 0, sc_map::max));
        data_organizer_it->proc_unit_outputs.bind(trigger_tower_interconnect(do_nr, do_nr, 0, sc_map::max));

        ++do_nr;
    }

    for (unsigned int po_id=0; po_id < prb_nr; ++po_id)
    {
        std::stringstream po_name;
        po_name << "processorOrganizer_" << po_id;
        processorOrganizers[po_id] = new processor_organizer(po_name.str().c_str(), po_id);
        processorOrganizers[po_id]->clk.bind(clk);
        processorOrganizers[po_id]->do_inputs.bind(trigger_tower_interconnect(0, sc_map::max, po_id, po_id));
        processorOrganizers[po_id]->processor_outputs.bind(am_board_in_sig(po_id, po_id, 0, sc_map::max, 0, sc_map::max));
    }

    sc_map_square<am_board>::iterator am_board_it = amBoards.begin();
    unsigned int am_board_id = 0;
    for (; am_board_it != amBoards.end(); ++am_board_it)
    {
        sc_map_square<am_board>::full_key_type am_board_key = amBoards.get_key(*am_board_it).second;

        am_board_it->clk.bind(clk);
        am_board_it->frame_inputs.bind(am_board_in_sig(am_board_key.Y_dim, am_board_key.Y_dim, am_board_key.X_dim, am_board_key.X_dim, 0, sc_map::max));
        am_board_it->hit_output.bind(hit_outputs(am_board_id, am_board_id, 0, sc_map::max));

        ++am_board_id;
    }

	return;
}
