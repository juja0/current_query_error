# Repro for current_query error when client_context.GetCurrentQuery() is called in an optimizer extension

Steps to reproduce the issue.

1. Execute "make debug"
2. run any query. It should fail with "INTERNAL Error: Assertion triggered in file "./duckdb/src/main/client_context.cpp" on line 286: active_query"

Extension code is in: src/quack_extension.cpp (look for SimpleLoggingExtension)

Fails on both v1.0.0 and on latest main

