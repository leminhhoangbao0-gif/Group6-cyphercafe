#pragma once

#include <QWidget>
#include "AuthController.h"

namespace Ui {
class RegisterWindow;
}

// RegisterWindow shows the sign-up form and talks to AuthController.
class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(AuthController* authController, QWidget* parent = nullptr);
    ~RegisterWindow();

signals:
    // Emitted when the user clicks "Already have an account? Log in" -
    // Member 6 connects this to switch back to the LoginWindow.
    void goToLoginRequested();

    // Emitted after a successful registration.
    void registrationSuccessful(const User& user);

private slots:
    void onRegisterButtonClicked();
    void onGoToLoginClicked();

private:
    Ui::RegisterWindow* ui;
    AuthController* m_authController;

    void showError(const QString& message);
    void clearError();
};
