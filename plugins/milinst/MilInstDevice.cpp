/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * MilInstDevice.cpp
 * MilInst device
 * Copyright (C) 2013 Peter Newman
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <string>

#include "ola/Logging.h"
#include "olad/Preferences.h"
#include "olad/Universe.h"
#include "plugins/milinst/MilInstDevice.h"
#include "plugins/milinst/MilInstPort.h"
#include "plugins/milinst/MilInstWidget1463.h"

namespace ola {
namespace plugin {
namespace milinst {

using ola::AbstractPlugin;

/*
 * Create a new device
 *
 * @param owner  the plugin that owns this device
 * @param name  the device name
 * @param dev_path  path to the pro widget
 */
MilInstDevice::MilInstDevice(AbstractPlugin *owner,
                                   const string &name,
                                   const string &dev_path):
  Device(owner, name),
  m_path(dev_path),
  m_widget(NULL) {
    m_widget = new MilInstWidget1463();
}


/*
 * Destroy this device
 */
MilInstDevice::~MilInstDevice() {
  if (m_widget)
    delete m_widget;
}


/*
 * Start this device
 */
bool MilInstDevice::StartHook() {
  if (!m_widget)
    return false;

  if (!m_widget->Connect(m_path)) {
    OLA_WARN << "MilInstPlugin: failed to connect to " << m_path;
    return false;
  }

  if (!m_widget->DetectDevice()) {
    OLA_WARN << "MilInstPlugin: no device found at " << m_path;
    return false;
  }

  MilInstOutputPort *port = new MilInstOutputPort(this, 0, m_widget);
  AddPort(port);
  return true;
}


/*
 * Stop this device
 */
void MilInstDevice::PrePortStop() {
  // disconnect from widget
  m_widget->Disconnect();
}


/*
 * return the sd for this device
 */
ConnectedDescriptor *MilInstDevice::GetSocket() const {
  return m_widget->GetSocket();
}
}  // namespace milinst
}  // namespace plugin
}  // namespace ola
