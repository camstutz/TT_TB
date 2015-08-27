/*!
 * @file trigger_tower.cpp
 * @author Christian Amstutz
 * @date July 20, 2015
 *
 * @brief
 */

/*
 *  Copyright (c) 2015 by Christian Amstutz
 */

#include "trigger_tower.hpp"

// *****************************************************************************
trigger_tower::trigger_tower(const sc_module_name _name,
        trigger_tower_config configuration) :
        sc_module(_name),
        layer_nr(configuration.layer_nr),
        prb_nr(configuration.prb_nr),
        dtc_per_prb(configuration.dtc_per_prb),
        AM_boards_per_proc_unit(configuration.AM_boards_per_prb),
        clk("clk"),
        dtc_inputs(prb_nr, dtc_per_prb, "dtc_input"),
        hit_outputs(prb_nr, AM_boards_per_proc_unit, layer_nr, "hit_output"),
        trigger_tower_interconnect(prb_nr, prb_nr, "trigger_tower_interconnect"),
        am_board_in_sig(prb_nr, AM_boards_per_proc_unit, layer_nr, "am_board_sig"),
        dataOrganizers(prb_nr, "dataOrganizer", configuration.data_organizer),
        processorOrganizers(prb_nr, "processorOrganizer", configuration.processor_organizers),
        amBoards(prb_nr, AM_boards_per_proc_unit, "AM_Board", configuration.am_board)
{
    unsigned int do_id = 0;
    sc_map_linear<data_organizer>::iterator data_organizer_it = dataOrganizers.begin();
    for (; data_organizer_it != dataOrganizers.end(); ++data_organizer_it)
    {
        data_organizer_it->clk.bind(clk);
        data_organizer_it->dtc_inputs.bind(dtc_inputs(sc_map_square_key(do_id, 0), sc_map_square_key(do_id, dtc_per_prb-1)) );
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
        }
    }

	return;
}
