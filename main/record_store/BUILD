package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "record_store",
    srcs = ["record_store.cc"],
    hdrs = ["record_store.h"],
    deps = [
        ":record_interface",
        "@com_github_google_glog//:glog",
    ],
)

cc_library(
    name = "record_interface",
    hdrs = ["record_interface.h"],
)

cc_library(
    name = "record",
    srcs = ["record.cc"],
    hdrs = ["record.h"],
    deps = [
        ":record_interface",
    ],
)