# Repro for current_query error when client_context.GetCurrentQuery() is called in an optimizer extension

Steps to reproduce the issue.

1. Execute "make debug"
2. Launch duckdb: ./build/debug/duckdb 
3. run any query. It should fail with "INTERNAL Error: Assertion triggered in file "./duckdb/src/main/client_context.cpp" on line 286: active_query"

Extension code is in: src/quack_extension.cpp (look for SimpleLoggingExtension)

Fails on both v1.0.0 and on latest main

Note: This works without issue when executed via tests, so it could be related to the absence of an active transaction when query is prepared when executed in cli.

To verify: Execute the clion run configuration named "Run tests".  