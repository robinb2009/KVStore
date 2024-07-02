load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "kv_store_test",
    srcs = ["kv_store_test.cc"],
    deps = ["//main:kv_store"],
    timeout = "short",
)