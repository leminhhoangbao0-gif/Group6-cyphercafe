#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(AuthController* authController, QWidget* parent)
    : QWidget(parent),
      ui(new Ui::LoginWindow),
      m_authController(authController)
{
    ui->setupUi(this);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    connect(ui->goToRegisterButton, &QPushButton::clicked, this, &LoginWindow::onGoToRegisterClicked);

    // Allow pressing Enter in the password field to submit the form.
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginButtonClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::onLoginButtonClicked()
{
    clearError();

    const QString username = ui->usernameLineEdit->text().trimmed();
    const QString password = ui->passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        showError("Please enter both username and password.");
        return;
    }

    QString errorMessage;
    if (m_authController->login(username, password, errorMessage)) {
        ui->passwordLineEdit->clear();
        emit loginSuccessful(m_authController->currentUser().value());
    } else {
        showError(errorMessage);
    }
}

void LoginWindow::onGoToRegisterClicked()
{
    emit goToRegisterRequested();
}

void LoginWindow::showError(const QString& message)
{
    ui->errorLabel->setText(message);
}

void LoginWindow::clearError()
{
    ui->errorLabel->setText("");
}
