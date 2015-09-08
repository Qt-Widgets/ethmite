/*
 * File:   IoForm.cpp
 * Author: Taran
 *
 * Created on 14 Май 2015 г., 17:14
 */

#include "IoForm.h"

IoForm::IoForm(EthInterface *com, uint32_t addr, uint32_t offset, 
        IoDataTypes type, const QString title) {
    widget.setupUi(this);

    this->com = com;
    cmd.cmd  = EthInterface::CmdWrite;
    cmd.addr = addr;
    cmd.offset = offset / sizeof(uint32_t);
    this->type = type;
    
    switch (type) {
        case IoForm::FLOAT:
            cmd.length = sizeof(float) / sizeof(uint32_t);
            validator = new QDoubleValidator();
            break;
        case IoForm::UINT32:
            cmd.length = sizeof(uint32_t) / sizeof(uint32_t);
            validator = new QIntValidator();
            break;
        case IoForm::INT32:
            cmd.length = sizeof(int32_t) / sizeof(uint32_t);
            validator = new QIntValidator();
            break;
        case IoForm::UINT8:
            cmd.length = sizeof(uint32_t) / sizeof(uint32_t);
            validator = new QIntValidator();
            break;
        default:
            cmd.length = sizeof(uint32_t) / sizeof(uint32_t);
            validator = new QIntValidator();
            break;
    }

    widget.leValue->setValidator(validator);
    widget.groupBox->setTitle(title);
    connect(widget.btnSet, SIGNAL(clicked()), this, SLOT(set()));
}

IoForm::~IoForm() {
}

void IoForm::set() {
    bool ok;
    float value;
    switch (type) {
        case IoForm::FLOAT:
            value = widget.leValue->text().toFloat(&ok);
            cmd.value = *((uint32_t *)&value);
            break;
        case IoForm::UINT32:
            cmd.value = widget.leValue->text().toUInt(&ok, 10);
            break;
        case IoForm::UINT8:
            cmd.value = widget.leValue->text().toUInt(&ok, 10) & 0xFF;
            break;
        case IoForm::INT32:
        default:
            cmd.value = widget.leValue->text().toInt(&ok, 10);
            break;
    }
    if (ok) {
        com->sendPacket((uint32_t *)&cmd, sizeof(cmd) / sizeof(uint32_t));
    }
}

void IoForm::setChannel(uint32_t channel) {
    cmd.addr = (cmd.addr & 0x0000FFFF) | ((channel << 16) & 0xFFFF0000);
}

QLineEdit* IoForm::getLineEdit() {
    return widget.leValue;
}
