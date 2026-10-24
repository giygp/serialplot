/*
  Copyright © 2025 Hasan Yavuz Özderya

  This file is part of serialplot.

  serialplot is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  serialplot is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with serialplot.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QByteArray>
#include <QtDebug>
#include <QSerialPort>
#include <QTcpSocket>

#include "command/commandpanel.h"
#include "ui_commandpanel.h"
#include "app/setting_defines.h"

CommandPanel::CommandPanel(QIODevice* device, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommandPanel),
    _menu(tr("&Commands")), _newCommandAction(tr("&New Command"), this)
{
    _device = device;

    ui->setupUi(this);
    auto layout = new QVBoxLayout();
    layout->setSpacing(0);
    ui->scrollAreaWidgetContents->setLayout(layout);

    connect(ui->pbNew, &QPushButton::clicked, this, &CommandPanel::newCommand);
    connect(&_newCommandAction, &QAction::triggered, this, &CommandPanel::newCommand);

    _menu.addAction(&_newCommandAction);
    _menu.addSeparator();

    command_name_counter = 0;
}

CommandPanel::~CommandPanel()
{
    commands.clear(); // UI will 'delete' actual objects
    delete ui;
}

CommandWidget* CommandPanel::newCommand()
{
    auto command = new CommandWidget();
    command_name_counter++;
    command->setName(tr("Command ") + QString::number(command_name_counter));
    ui->scrollAreaWidgetContents->layout()->addWidget(command);
    command->setFocusToEdit();
    connect(command, &CommandWidget::sendCommand, this, &CommandPanel::sendCommand);
    connect(command, &CommandWidget::focusRequested, this, &CommandPanel::focusRequested);
    _menu.addAction(command->sendAction());

    // add to command list and remove on destroy
    commands << command;
    connect(command, &QObject::destroyed, [this](QObject* obj)
            {
                commands.removeOne(static_cast<CommandWidget*>(obj));
                reAssignShortcuts();
            });

    reAssignShortcuts();
    return command;
}

void CommandPanel::reAssignShortcuts()
{
    // can assign shortcuts to first 12 commands
    for (int i = 0; i < std::min(12, (int)commands.size()); i++)
    {
        auto cmd = commands[i];
        cmd->sendAction()->setShortcut(QKeySequence(Qt::Key_F1 + i));
    }
}

void CommandPanel::sendCommand(QByteArray command)
{
    if (_device == NULL)
    {
        qCritical() << "Cannot send command: no device is selected!";
        return;
    }

    if (!_device->isOpen())
    {
        qCritical() << "Cannot send command: device is not open."
                       " Open the serial port or connect TCP first.";
        updateTargetLabel();
        return;
    }

    if (_device->write(command) < 0)
    {
        qCritical() << "Send command failed!";
    }
}

QMenu* CommandPanel::menu()
{
    return &_menu;
}

QAction* CommandPanel::newCommandAction()
{
    return &_newCommandAction;
}

unsigned CommandPanel::numOfCommands()
{
    return commands.size();
}

void CommandPanel::saveSettings(QSettings* settings)
{
    settings->beginGroup(SettingGroup_Commands);
    settings->beginWriteArray(SG_Commands_Command);
    for (int i = 0; i < commands.size(); i ++)
    {
        settings->setArrayIndex(i);
        auto command = commands[i];
        settings->setValue(SG_Commands_Name, command->name());
        settings->setValue(SG_Commands_Type, command->isASCIIMode() ? "ascii" : "hex");
        settings->setValue(SG_Commands_Data, command->commandText());
    }
    settings->endArray();
    settings->endGroup();
}

void CommandPanel::loadSettings(QSettings* settings)
{
    // clear all commands
    while (commands.size())
    {
        auto command = commands.takeLast();
        command->disconnect();
        delete command;
    }

    // load commands
    settings->beginGroup(SettingGroup_Commands);
    unsigned size = settings->beginReadArray(SG_Commands_Command);

    for (unsigned i = 0; i < size; i ++)
    {
        settings->setArrayIndex(i);
        auto command = newCommand();

        // load command name
        QString name = settings->value(SG_Commands_Name, "").toString();
        if (!name.isEmpty()) command->setName(name);

        // Important: type should be set before command data for correct validation
        QString type = settings->value(SG_Commands_Type, "").toString();
        if (type == "ascii")
        {
            command->setASCIIMode(true);
        }
        else if (type == "hex")
        {
            command->setASCIIMode(false);
        } // else unchanged

        // load command data
        command->setCommandText(settings->value(SG_Commands_Data, "").toString());
    }

    settings->endArray();
    settings->endGroup();
}

void CommandPanel::setDevice(QIODevice* device)
{
    _device = device;
    updateTargetLabel();
}

void CommandPanel::updateTargetLabel()
{
    if (ui == NULL || ui->lbTarget == NULL) return;

    QString text;
    if (_device == NULL)
    {
        text = tr("Send via: none");
    }
    else if (auto serial = qobject_cast<QSerialPort*>(_device))
    {
        QString name = serial->portName().isEmpty() ?
                       tr("Serial Port") : serial->portName();
        text = tr("Send via: Serial (%1)").arg(name);
    }
    else if (auto tcp = qobject_cast<QTcpSocket*>(_device))
    {
        if (tcp->peerAddress().isNull() || tcp->peerAddress().toString().isEmpty())
        {
            text = tr("Send via: TCP");
        }
        else
        {
            text = tr("Send via: TCP (%1:%2)")
                   .arg(tcp->peerAddress().toString()).arg(tcp->peerPort());
        }
    }
    else
    {
        text = tr("Send via: device");
    }

    if (_device != NULL && !_device->isOpen())
    {
        text += tr("  [not connected]");
    }

    ui->lbTarget->setText(text);
}
