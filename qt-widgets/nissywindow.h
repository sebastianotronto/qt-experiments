#ifndef NISSYWINDOW_H
#define NISSYWINDOW_H

#include "adapter.h"
#include "solvercfgwidget.h"

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class NissyWindow;
}
QT_END_NAMESPACE

class NissyWindow : public QMainWindow
{
	Q_OBJECT

public:
	NissyWindow(QWidget *parent = nullptr);
	~NissyWindow();

private slots:
	void showSolutions(QString);
	void startSolve(const SolverConfiguration&);

private:
	Ui::NissyWindow *ui;
	NissyAdapter adapter;
};

#endif
