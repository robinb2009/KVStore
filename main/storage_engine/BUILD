package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "storage_engine_interface",
    hdrs = ["storage_engine_interface.h"],
)

cc_library(
    name = "b_plus_tree",
    srcs = ["b_plus_tree.cc"],
    hdrs = ["b_plus_tree.h"],
    deps = [
        ":storage_engine_interface",
        "@com_github_google_glog//:glog",
    ],
)