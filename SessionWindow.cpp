#include "SessionWindow.h"
#include "ui_SessionWindow.h"

#include <QAbstractItemView>
#include <QHeaderView>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QStringList>
#include <QTableWidgetItem>

SessionWindow::SessionWindow(SessionManager *sessionManager, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::SessionWindow),
      m_sessionManager(sessionManager)
{
    ui->setupUi(this);
    configureTables();

    connect(ui->startButton, &QPushButton::clicked, this, &SessionWindow::startSelectedSession);
    connect(ui->endButton, &QPushButton::clicked, this, &SessionWindow::endSelectedSession);
    connect(ui->lockButton, &QPushButton::clicked, this, &SessionWindow::lockSelectedPc);
    connect(ui->unlockButton, &QPushButton::clicked, this, &SessionWindow::unlockSelectedPc);

    if (m_sessionManager) {
        connect(m_sessionManager, &SessionManager::pcsChanged, this, &SessionWindow::refreshPcs);
        connect(m_sessionManager, &SessionManager::sessionsChanged, this, &SessionWindow::refreshSessions);
        connect(m_sessionManager, &SessionManager::errorOccurred, this, &SessionWindow::showError);
        connect(m_sessionManager, &SessionManager::sessionExpired, this, [this](int pcId) {
            QMessageBox::information(this, "Session expired", QString("PC %1 has been locked.").arg(pcId));
        });

        m_sessionManager->load();
    }
}

SessionWindow::~SessionWindow()
{
    delete ui;
}

void SessionWindow::configureTables()
{
    ui->pcTable->setColumnCount(3);
    ui->pcTable->setHorizontalHeaderLabels(QStringList() << "ID" << "PC" << "Status");
    ui->pcTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->pcTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->pcTable->horizontalHeader()->setStretchLastSection(true);

    ui->sessionTable->setColumnCount(5);
    ui->sessionTable->setHorizontalHeaderLabels(QStringList() << "ID" << "PC" << "Customer" << "Minutes" << "Status");
    ui->sessionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->sessionTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->sessionTable->horizontalHeader()->setStretchLastSection(true);
}

void SessionWindow::refreshPcs()
{
    if (!m_sessionManager) {
        return;
    }

    const QList<PC> pcs = m_sessionManager->pcs();
    ui->pcTable->setRowCount(pcs.size());

    for (int row = 0; row < pcs.size(); ++row) {
        const PC pc = pcs.at(row);
        ui->pcTable->setItem(row, 0, new QTableWidgetItem(QString::number(pc.id())));
        ui->pcTable->setItem(row, 1, new QTableWidgetItem(pc.name()));
        ui->pcTable->setItem(row, 2, new QTableWidgetItem(pc.statusText()));
    }
}

void SessionWindow::refreshSessions()
{
    if (!m_sessionManager) {
        return;
    }

    const QList<Session> sessions = m_sessionManager->activeSessions();
    ui->sessionTable->setRowCount(sessions.size());

    for (int row = 0; row < sessions.size(); ++row) {
        const Session session = sessions.at(row);
        ui->sessionTable->setItem(row, 0, new QTableWidgetItem(QString::number(session.id())));
        ui->sessionTable->setItem(row, 1, new QTableWidgetItem(QString::number(session.pcId())));
        ui->sessionTable->setItem(row, 2, new QTableWidgetItem(QString::number(session.customerId())));
        ui->sessionTable->setItem(row, 3, new QTableWidgetItem(QString::number(session.durationMinutes())));
        ui->sessionTable->setItem(row, 4, new QTableWidgetItem(session.statusText()));
    }
}

void SessionWindow::startSelectedSession()
{
    const int pcId = selectedPcId();
    if (pcId <= 0 || !m_sessionManager) {
        return;
    }

    m_sessionManager->startSession(pcId,
                                   ui->customerIdSpinBox->value(),
                                   ui->durationSpinBox->value());
}

void SessionWindow::endSelectedSession()
{
    const int pcId = selectedPcId();
    if (pcId > 0 && m_sessionManager) {
        m_sessionManager->endSession(pcId);
    }
}

void SessionWindow::lockSelectedPc()
{
    const int pcId = selectedPcId();
    if (pcId > 0 && m_sessionManager) {
        m_sessionManager->lockPc(pcId);
    }
}

void SessionWindow::unlockSelectedPc()
{
    const int pcId = selectedPcId();
    if (pcId > 0 && m_sessionManager) {
        m_sessionManager->unlockPc(pcId);
    }
}

void SessionWindow::showError(const QString &message)
{
    QMessageBox::warning(this, "Session management", message);
}

int SessionWindow::selectedPcId() const
{
    const QList<QTableWidgetItem *> selected = ui->pcTable->selectedItems();
    if (selected.isEmpty()) {
        return 0;
    }

    return ui->pcTable->item(selected.first()->row(), 0)->text().toInt();
}
