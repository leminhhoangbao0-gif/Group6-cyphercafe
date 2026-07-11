#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"

RegisterWindow::RegisterWindow(AuthController* authController, QWidget* parent)
    : QWidget(parent),
      ui(new Ui::RegisterWindow),
      m_authController(authController)
{
    ui->setupUi(this);

    connect(ui->registerButton, &QPushButton::clicked, this, &RegisterWindow::onRegisterButtonClicked);
    connect(ui->goToLoginButton, &QPushButton::clicked, this, &RegisterWindow::onGoToLoginClicked);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::onRegisterButtonClicked()
{
    clearError();

    const QString username = ui->usernameLineEdit->text().trimmed();
    const QString fullName = ui->fullNameLineEdit->text().trimmed();
    const QString email = ui->emailLineEdit->text().trimmed();
    const QString phone = ui->phoneLineEdit->text().trimmed();
    const QString password = ui->passwordLineEdit->text();
    const QString confirmPassword = ui->confirmPasswordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        showError("Username and password are required.");
        return;
    }

    if (password != confirmPassword) {
        showError("Passwords do not match.");
        return;
    }

    QString errorMessage;
    if (m_authController->registerUser(username, password, fullName, email, phone, errorMessage)) {
        ui->passwordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();
        emit registrationSuccessful(m_authController->currentUser().value_or(User()));
        emit goToLoginRequested(); // send them to log in with their new account
    } else {
        showError(errorMessage);
    }
}

void RegisterWindow::onGoToLoginClicked()
{
    emit goToLoginRequested();
}

void RegisterWindow::showError(const QString& message)
{
    ui->errorLabel->setText(message);
}

void RegisterWindow::clearError()
{
    ui->errorLabel->setText("");
}
