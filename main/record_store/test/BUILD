load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "record_store_test",
    srcs = ["record_store_test.cc"],
    deps = [
        "//main/record_store:record_store",
        "//main/record_store:record",
        "//main/utils:test_util",
    ],
    timeout = "short",
)