load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "b_plus_tree_test",
    srcs = ["b_plus_tree_test.cc"],
    deps = [
        "//main/storage_engine:b_plus_tree",
        "//main/utils:test_util",
    ],
    timeout = "short",
)