#include "solvercfgwidget.h"
#include "./ui_solvercfgwidget.h"

enum class ScrambleState { empty, valid, invalid };

ScrambleState getScrambleState(const std::string&);

SolverCfgWidget::SolverCfgWidget(QWidget *parent)
	: QWidget(parent), ui(new Ui::SolverCfgWidget)
{
	ui->setupUi(this);
        onScrambleChanged(ui->scrambleEditor->text());

	nmovesValidator = new QIntValidator(0, 20, this);
	ui->minMovesEditor->setValidator(nmovesValidator);
	ui->maxMovesEditor->setValidator(nmovesValidator);

	QObject::connect(ui->scrambleEditor,
	    SIGNAL(textChanged(const QString&)), this,
	    SLOT(onScrambleChanged(const QString&)));
	QObject::connect(ui->scrambleEditor, SIGNAL(returnPressed()),
	    this, SLOT(onScrambleSubmitted()));
	QObject::connect(ui->solveButton, SIGNAL(clicked()),
	    this, SLOT(onScrambleSubmitted()));
}

SolverCfgWidget::~SolverCfgWidget()
{
	delete nmovesValidator;
	delete ui;
}

void SolverCfgWidget::lockSubmit()
{
	submitLocked = true;
	onScrambleChanged(ui->scrambleEditor->text());
}

void SolverCfgWidget::unlockSubmit()
{
	submitLocked = false;
	onScrambleChanged(ui->scrambleEditor->text());
}

void SolverCfgWidget::onScrambleChanged(const QString& text)
{
	auto scrambleState = getScrambleState(text.toStdString());
	switch (scrambleState) {
	case ScrambleState::empty:
		ui->solveButton->setEnabled(false);
		ui->scrambleEditor->setStyleSheet("");
		break;
	case ScrambleState::valid:
		ui->solveButton->setEnabled(!submitLocked);
		ui->scrambleEditor->setStyleSheet("");
		break;
	case ScrambleState::invalid:
		ui->solveButton->setEnabled(false);
		ui->scrambleEditor->setStyleSheet("border : 2px solid red");
		break;
	}
}

void SolverCfgWidget::onScrambleSubmitted()
{
	std::string scramble = ui->scrambleEditor->text().toStdString();
	auto state = getScrambleState(scramble);
	if (state != ScrambleState::valid)
		return;

	SolverConfiguration sc {
		.cube = std::get<nissy::cube_t>(nissy::applymoves(
		    nissy::cube::SOLVED, nissy::moves_t{scramble})),
		.minmoves = ui->minMovesEditor->text().toUInt(),
		.maxmoves = ui->maxMovesEditor->text().toUInt(),
	};
	emit solveRequest(sc);
}

ScrambleState getScrambleState(const std::string& s)
{
	if (std::all_of(s.begin(), s.end(),
	   [](std::string::value_type c){ return std::isspace(c); }))
		return ScrambleState::empty;

	auto c = nissy::applymoves(nissy::cube::SOLVED, nissy::moves_t{s});
	return std::holds_alternative<nissy::error_t>(c) ?
	    ScrambleState::invalid : ScrambleState::valid;
}

