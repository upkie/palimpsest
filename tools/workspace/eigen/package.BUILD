# -*- python -*-
#
# Copyright 2022 Stéphane Caron

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "eigen",
    hdrs = glob([
        "Eigen/**",
    ]),
    includes = ["."],
    defines = [
        "EIGEN_MPL2_ONLY",
    ],
)
