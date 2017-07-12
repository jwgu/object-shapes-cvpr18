//
// Created by daeyun on 6/29/17.
//

#include "flags.h"
#include <gflags/gflags.h>

DEFINE_string(data_dir, "/data/mvshape", "data directory");
DEFINE_string(out_dir, "/data/mvshape/out", "output directory.");
DEFINE_string(resources_dir, "", "Path to 'resources' directory.");
DEFINE_bool(is_test_mode, false, "Indicates if this is a test run.");
DEFINE_string(tf_model, "", "Path to saved tensorflow model.");
DEFINE_string(run_id, "default", "A name that identifies the current experiment.");
