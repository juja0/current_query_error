#define DUCKDB_EXTENSION_MAIN

#include "quack_extension.hpp"

#include "duckdb.hpp"
#include "duckdb/common/exception.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb/function/scalar_function.hpp"
#include "duckdb/main/extension_util.hpp"

#include <duckdb/parser/parsed_data/create_scalar_function_info.hpp>

namespace duckdb {

class SimpleLoggingExtension : public OptimizerExtension {
public:
	SimpleLoggingExtension() {
		optimize_function = optimize;
	}

	static void optimize(OptimizerExtensionInput &input, unique_ptr<LogicalOperator> &plan) {
		Printer::Print("Current query is: " + input.context.GetCurrentQuery());
	}
};

static void LoadInternal(DatabaseInstance &instance) {
	DBConfig::GetConfig(instance).optimizer_extensions.push_back(SimpleLoggingExtension());
}

void QuackExtension::Load(DuckDB &db) {
	LoadInternal(*db.instance);
}
std::string QuackExtension::Name() {
	return "quack";
}

std::string QuackExtension::Version() const {
#ifdef EXT_VERSION_QUACK
	return EXT_VERSION_QUACK;
#else
	return "";
#endif
}

} // namespace duckdb

extern "C" {

DUCKDB_EXTENSION_API void quack_init(duckdb::DatabaseInstance &db) {
	duckdb::DuckDB db_wrapper(db);
	db_wrapper.LoadExtension<duckdb::QuackExtension>();
}

DUCKDB_EXTENSION_API const char *quack_version() {
	return duckdb::DuckDB::LibraryVersion();
}
}

#ifndef DUCKDB_EXTENSION_MAIN
#error DUCKDB_EXTENSION_MAIN not defined
#endif
