#include <QMessageBox>
#include <QString>
#include <QObject>
#include <QApplication>

enum class DialogButton
{
    AbortRetryIgnore = 0x00000002L,
    Ok = 0x00000000L,
    OkCancel = 0x00000001L,
    RetryCancel = 0x00000005L,
    YesNo = 0x00000004L,
    YesNoCancel = 0x00000003L,
    CancelTryContinue = 0x00000006L,
};

enum class DialogIcon
{
    Exclamation = 0x00000030L,
    Information = 0x00000040L,
    Error = 0x00000010L,
    None = 0
};
enum class DialogResult
{
    Abort = 3,
    Cancel = 2,
    Continue = 11,
    Ignore = 5,
    No = 7,
    Ok = 1,
    Retry = 4,
    TryAgain = 10,
    Yes = 6,
    Failed = 0
};

extern "C"
{
    DialogResult ShowMessageDialog(char *caption, char *text, DialogButton button, DialogIcon icon);
}

//Constructs a QApplication to make QMessageBox useable.
static int argc = 0;
static QApplication app(argc, nullptr);

DialogResult ShowMessageDialog(char *caption, char *text, DialogButton button, DialogIcon icon)
{
    QMessageBox msgBox;
    msgBox.setText(QString(text));
    msgBox.setInformativeText(QString(caption));
    switch (icon)
    {
    case DialogIcon::Error:
        msgBox.setIcon(QMessageBox::Critical);
        break;
    case DialogIcon::Information:
        msgBox.setIcon(QMessageBox::Information);
        break;
    case DialogIcon::Exclamation:
        msgBox.setIcon(QMessageBox::Warning);
        break;
    default:
        break;
    }
    QPushButton *abort = nullptr, *retry = nullptr, *ignore = nullptr,
                *cancel = nullptr, *tryBtn = nullptr, *continueBtn = nullptr,
                *ok = nullptr, *yes = nullptr, *no = nullptr;
    switch (button)
    {
    case DialogButton::AbortRetryIgnore:
        abort = msgBox.addButton(QMessageBox::Abort);
        retry = msgBox.addButton(QMessageBox::Retry);
        ignore = msgBox.addButton(QMessageBox::Ignore);
        msgBox.exec();
        if ((QPushButton *)msgBox.clickedButton() == abort)
            return DialogResult::Abort;
        if ((QPushButton *)msgBox.clickedButton() == retry)
            return DialogResult::Retry;
        if ((QPushButton *)msgBox.clickedButton() == ignore)
            return DialogResult::Ignore;
        return DialogResult::Failed;
    case DialogButton::CancelTryContinue:
        cancel = msgBox.addButton(QMessageBox::Cancel);
        tryBtn = msgBox.addButton(QObject::tr("Try Again"), QMessageBox::ActionRole);
        continueBtn = msgBox.addButton(QObject::tr("Continue"), QMessageBox::ActionRole);
        msgBox.exec();
        if ((QPushButton *)msgBox.clickedButton() == cancel)
            return DialogResult::Cancel;
        if ((QPushButton *)msgBox.clickedButton() == tryBtn)
            return DialogResult::TryAgain;
        if ((QPushButton *)msgBox.clickedButton() == continueBtn)
            return DialogResult::Continue;
        return DialogResult::Failed;
    case DialogButton::Ok:
        ok = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        if ((QPushButton *)msgBox.clickedButton() == ok)
            return DialogResult::Ok;
        return DialogResult::Failed;
    case DialogButton::YesNo:
        yes = msgBox.addButton(QMessageBox::Yes);
        no = msgBox.addButton(QMessageBox::No);
        msgBox.exec();
        if ((QPushButton *)msgBox.clickedButton() == yes)
            return DialogResult::Yes;
        if ((QPushButton *)msgBox.clickedButton() == no)
            return DialogResult::No;
        return DialogResult::Failed;
    case DialogButton::OkCancel:
        ok = msgBox.addButton(QMessageBox::Ok);
        goto addCancel;
    case DialogButton::RetryCancel:
        retry = msgBox.addButton(QMessageBox::Retry);
        goto addCancel;
    case DialogButton::YesNoCancel:
        yes = msgBox.addButton(QMessageBox::Yes);
        no = msgBox.addButton(QMessageBox::No);
    addCancel:
        cancel = msgBox.addButton(QMessageBox::Cancel);
        msgBox.exec();
        if (msgBox.clickedButton() == nullptr)
            return DialogResult::Failed;
        if ((QPushButton *)msgBox.clickedButton() == yes)
            return DialogResult::Yes;
        if ((QPushButton *)msgBox.clickedButton() == no)
            return DialogResult::No;
        if ((QPushButton *)msgBox.clickedButton() == retry)
            return DialogResult::Retry;
        if ((QPushButton *)msgBox.clickedButton() == cancel)
            return DialogResult::Cancel;
        if ((QPushButton *)msgBox.clickedButton() == ok)
            return DialogResult::Ok;
    default:
        return DialogResult::Failed;
    }
}