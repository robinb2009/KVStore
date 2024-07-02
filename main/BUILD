package(default_visibility = ["//visibility:public"])

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_binary(
    name = "kv_store_exec",
    srcs = ["kv_store_exec.cc"],
    deps = [":kv_store"],
)

cc_library(
    name = "kv_store",
    srcs = ["kv_store.cc"],
    hdrs = ["kv_store.h"],
    deps = ["@com_github_google_glog//:glog"],
)