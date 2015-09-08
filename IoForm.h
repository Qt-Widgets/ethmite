/* 
 * File:   IoForm.h
 * Author: Taran
 *
 * Created on 14 Май 2015 г., 17:14
 */

#ifndef _IOFORM_H
#define	_IOFORM_H

#include "ui_IoForm.h"
#include "EthlInterface.h"

class IoForm : public QWidget {
    Q_OBJECT
public:
    
    enum IoDataTypes {
        FLOAT, UINT32, INT32, UINT8
    };
    
    IoForm(EthInterface *com, uint32_t addr, uint32_t offset, 
        IoDataTypes type, const QString title);
    virtual ~IoForm();
    QLineEdit* getLineEdit();
    void setChannel(uint32_t channel);
private:
    IoDataTypes type;
    Ui::IoForm widget;
    QValidator *validator;
    EthInterface *com;
    EthInterface::command cmd;
    
public slots:
    void set();
};

#endif	/* _IOFORM_H */
