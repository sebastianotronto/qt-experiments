#ifndef ADAPTER_H
#define ADAPTER_H

#include "../nissy-core/cpp/nissy.h"

#include <string>
#include <vector>
#include <QObject>

struct SolverConfiguration {
	nissy::cube cube{nissy::cube::SOLVED};
	unsigned minmoves{0};
	unsigned maxmoves{20};
	unsigned maxsolutions{1};
	int optimal{-1};
	int threads{8};
};

class NissyAdapter : public QObject {
	Q_OBJECT

public:
	NissyAdapter();
	~NissyAdapter();
	void solve(SolverConfiguration);

signals:
	void solveDone(QString);

private:
	static constexpr nissy::solver defaultOptimalSolver{"h48h3k2"};
	nissy::solver_data_t optimalSolverData;
};

#endif
