#ifndef SOLVERCFGWIDGET_H
#define SOLVERCFGWIDGET_H

#include "adapter.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QIntValidator>

QT_BEGIN_NAMESPACE
namespace Ui {
class SolverCfgWidget;
}
QT_END_NAMESPACE

class SolverCfgWidget : public QWidget
{
	Q_OBJECT

public:
	SolverCfgWidget(QWidget *parent);
	~SolverCfgWidget();

	void lockSubmit();
	void unlockSubmit();

signals:
	void solveRequest(const SolverConfiguration&);

private slots:
	void onScrambleChanged(const QString&);
	void onScrambleSubmitted();

private:
	bool submitLocked;
	QIntValidator *nmovesValidator;

	Ui::SolverCfgWidget *ui;
};

#endif
