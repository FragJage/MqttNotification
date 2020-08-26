MqttNotification
=========
Mqtt daemon can display messages with os notification.

Introduction
============
This daemon can display some messages by using operating system notifications.

Features
========
 - Specify a machine or all machine
 - Specify a title

MQTT Message
============
Topic /notification/command/Hostname or /notification/command/ALL
Body {"title":"My test", "body":"Hello world !"}

Licence
=======
MqttNotification is free software : you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

MqttNotification is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with MqttNotification. If not, see http://www.gnu.org/licenses/.
