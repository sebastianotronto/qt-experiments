#include "adapter.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <QDebug>

NissyAdapter::NissyAdapter()
{
	auto sid = nissy::solverinfo(defaultOptimalSolver);
	auto [sz, dataid] = std::get<std::pair<size_t, std::string>>(sid);
	const std::string path = "../nissy-core/tables/" + dataid;

	std::filesystem::path filePath(path);
	if (std::filesystem::file_size(filePath) != static_cast<uintmax_t>(sz))
		qDebug("Error in file size!"); // TODO: better handle error, gentable

	optimalSolverData.value.resize(sz);
	std::ifstream ifs(path, std::ios::binary);
	ifs.read(reinterpret_cast<char *>(optimalSolverData.value.data()), sz);
	ifs.close();
}

NissyAdapter::~NissyAdapter() {}

void NissyAdapter::solve(SolverConfiguration cfg)
{
	auto se = nissy::solve(cfg.cube, defaultOptimalSolver,
	    nissy::nissflag::NORMAL, cfg.minmoves, cfg.maxmoves,
	    cfg.maxsolutions, cfg.optimal, cfg.threads, optimalSolverData);
	if (std::holds_alternative<nissy::error_t>(se)) {
		auto code = std::get<nissy::error_t>(se).value;
		emit solveDone(QString("Error " + code));
		return;
	} 

	auto [sols, stats] = std::get<nissy::solve_result_t>(se);
	if (sols.size() == 0) {
		emit solveDone(QString("No solution found"));
	} else {
		auto solstr = std::accumulate(
		    sols.begin(), sols.end(), std::string{});
		emit solveDone(QString::fromStdString(solstr));
	}
}
