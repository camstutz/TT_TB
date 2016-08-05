/*!
 * @file trigger_tower.cpp
 * @author Christian Amstutz
 * @date August 4, 2016
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower.hpp"

// *****************************************************************************
trigger_tower::trigger_tower(const sc_module_name _name,
        const trigger_tower_config& configuration) :
        sc_module(_name),
        configuration(&configuration),
        layer_nr(configuration.layers.size()),
        prb_nr(configuration.type.prb_nr),
        dtc_per_prb(configuration.type.dtc_per_prb),
        AM_boards_per_proc_unit(configuration.type.AM_boards_per_prb),
        clk("clk"),
        dtc_inputs(configuration.DTC_ids, "dtc_input"),
        hit_outputs(prb_nr, AM_boards_per_proc_unit, layer_nr, "hit_output"),
        trigger_tower_interconnect(configuration.data_organizers.size(), prb_nr, "trigger_tower_interconnect"),
        am_board_in_sig(prb_nr, AM_boards_per_proc_unit, layer_nr, "am_board_sig"),
        dataOrganizers(configuration.data_organizers.size(), "dataOrganizer", configuration.data_organizers),
        processorOrganizers(prb_nr, "processorOrganizer", configuration.processor_organizers),
        amBoards(prb_nr, AM_boards_per_proc_unit, "AM_Board", configuration.type.am_board),
        patternBank(configuration.layers.size())
{
    patternBank.generate_patterns_straight(1000);

    unsigned int do_id = 0;
    sc_map_linear<data_organizer>::iterator data_organizer_it = dataOrganizers.begin();
    for (; data_organizer_it != dataOrganizers.end(); ++data_organizer_it)
    {
        data_organizer_it->clk.bind(clk);

        sc_map_list_range<unsigned int> DO_dtc_range(data_organizer_it->configuration.get_dtcs());
        sc_map_list<unsigned int, sc_in<data_organizer::dtc_input_t> >::iterator dtc_input_it = dtc_inputs(DO_dtc_range);
        data_organizer_it->dtc_inputs.bind(dtc_input_it);

        data_organizer_it->proc_unit_outputs.bind(trigger_tower_interconnect(sc_map_square_key(do_id, 0), sc_map_square_key(do_id, prb_nr-1)));

        ++do_id;
    }

    for (unsigned int po_id=0; po_id < prb_nr; ++po_id)
    {
        processorOrganizers.at(po_id).clk.bind(clk);
        processorOrganizers.at(po_id).do_inputs.bind(trigger_tower_interconnect(sc_map_square_key(0, po_id), sc_map_square_key(prb_nr-1 , po_id)));
        processorOrganizers.at(po_id).processor_outputs.bind(am_board_in_sig(sc_map_cube_key(po_id, 0, 0), sc_map_cube_key(po_id, AM_boards_per_proc_unit-1, layer_nr-1)));
    }

    for (unsigned int prb_id = 0; prb_id < prb_nr; ++prb_id)
    {
        for (unsigned int am_board_id = 0; am_board_id < AM_boards_per_proc_unit; ++am_board_id)
        {
            am_board* am_board_ptr = &amBoards.at(prb_id, am_board_id);
            am_board_ptr->clk.bind(clk);
            am_board_ptr->frame_inputs.bind(am_board_in_sig(sc_map_cube_key(prb_id, am_board_id, 0), sc_map_cube_key(prb_id, am_board_id, layer_nr) ));
            am_board_ptr->hit_output.bind(hit_outputs(sc_map_cube_key(prb_id, am_board_id, 0), sc_map_cube_key(prb_id, am_board_id, layer_nr)));
            am_board_ptr->set_pattern_bank(&patternBank);
        }
    }

	return;
}
