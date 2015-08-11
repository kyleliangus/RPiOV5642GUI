#ifndef ISP_H
#define ISP_H

#include <QDialog>
#include <QGroupBox>
#include <string>
#include <QSettings>

#include "parameter.h"
#include "model.h"

namespace Ui {
class isp;
}

class isp : public QDialog
{
    Q_OBJECT

public:
    explicit isp(std::string, QWidget *parent = 0);
    ~isp();
    std::vector<Parameter> getISPParameters();

private slots:
    // Ui slots
    void formatControlCheck(bool);
    void showGroupBox(int);

    void obtainOptionsSelectedISP();
    void saveISPUIOptions( std::string );
    void loadISPUIOptions( std::string );
    void saveISPMenuState();
    void loadISPMenuState();

private:
    Ui::isp *ui;
    QGroupBox *ispGroupBoxes[8];
    std::vector<Parameter> ispParameters;
    std::string savedFileName;
};

#endif // ISP_H
