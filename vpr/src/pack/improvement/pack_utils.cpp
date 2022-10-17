//
// Created by elgammal on 2022-07-27.
//

#include "pack_utils.h"
#include "re_cluster.h"
#include "re_cluster_util.h"
#include "globals.h"
#include "clustered_netlist_fwd.h"
#include "move_utils.h"
#include "cluster_placement.h"
#include "packing_move_generator.h"
#include "pack_move_utils.h"


const int max_swaps = 5000;




void iteratively_improve_packing(t_clustering_data& clustering_data, int verbosity) {
    /*
    auto& cluster_ctx = g_vpr_ctx.clustering();
    auto& atom_ctx = g_vpr_ctx.atom();
    */
    int proposed = 0;
    int succeeded = 0;
    std::unique_ptr<packingMoveGenerator> move_generator;
    move_generator = std::make_unique<quasiDirectedPackingMove>();

    bool is_proposed, is_valid, is_successful;
    std::vector<molMoveDescription> new_locs;

    for(int i = 0; i < max_swaps; i++) {
        new_locs.clear();
        is_proposed = move_generator->propose_move(new_locs);
        if (!is_proposed) {
            VTR_LOGV(verbosity > 2, "Move failed! Can't propose.\n");
            continue;
        }

        is_valid = move_generator->evaluate_move(new_locs);
        if (!is_valid) {
            VTR_LOGV(verbosity > 2, "Move failed! Proposed move is bad.\n");
            continue;
        }

        proposed++;
        is_successful = move_generator->apply_move(new_locs, clustering_data);
        if (!is_successful) {
            VTR_LOGV(verbosity > 2, "Move failed! Proposed move isn't legal.\n");
            continue;
        }
        succeeded++;
        VTR_LOGV(verbosity > 1, "Packing move succeeded!\n");
    }
    VTR_LOG("@@@@ proposed = %zu, succeded %zu\n", proposed, succeeded);
}