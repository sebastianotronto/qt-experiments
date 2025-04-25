#include "nissywindow.h"
#include "./ui_nissywindow.h"
#include "nissy/cpp/nissy.h"

#include <QtConcurrent>

NissyWindow::NissyWindow(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::NissyWindow)
{
	ui->setupUi(this);

	QObject::connect(ui->solverCfgWidget,
	    SIGNAL(solveRequest(const SolverConfiguration&)), this,
	    SLOT(startSolve(const SolverConfiguration&)));
	QObject::connect(&adapter, SIGNAL(solveDone(QString)), this,
	    SLOT(showSolutions(QString)));
}

NissyWindow::~NissyWindow()
{
	delete ui;
}

void NissyWindow::startSolve(const SolverConfiguration& config)
{
	ui->solverCfgWidget->lockSubmit();
	ui->solutionsLabel->setText("Loading solutions...");
	auto _ = QtConcurrent::run(&NissyAdapter::solve, &adapter, config);
}

void NissyWindow::showSolutions(QString solutions) {
	QString header = QString("Solution(s) found:\n");
	ui->solutionsLabel->setText(header + solutions);
	ui->solverCfgWidget->unlockSubmit();
}
