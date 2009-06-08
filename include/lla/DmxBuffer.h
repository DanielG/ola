/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * DmxBuffer.h
 * Interface for the DmxBuffer
 * Copyright (C) 2005-2009 Simon Newton
 */

#ifndef LLA_DMX_BUFFER_H
#define LLA_DMX_BUFFER_H

#include <stdint.h>
#include <string>

namespace lla {

using std::string;

/*
 * The DmxBuffer class
 */
class DmxBuffer {
  public:
    DmxBuffer();
    DmxBuffer(const DmxBuffer &other);
    DmxBuffer(const uint8_t *data, unsigned int length);
    DmxBuffer(const string &data);
    ~DmxBuffer();
    DmxBuffer& operator=(const DmxBuffer &other);

    bool operator==(const DmxBuffer &other) const;
    unsigned int Size() const { return m_length; }

    bool HTPMerge(const DmxBuffer &other);
    bool Set(const uint8_t *data, unsigned int length);
    bool Set(const string &data);
    bool Set(const DmxBuffer &other);
    bool SetFromString(const string &data);
    bool SetRangeToValue(unsigned int offset, uint8_t data,
                         unsigned int length);
    bool SetRange(unsigned int offset, const uint8_t *data,
                  unsigned int length);
    void SetChannel(unsigned int channel, uint8_t data);
    void Get(uint8_t *data, unsigned int &length) const;
    uint8_t Get(unsigned int channel) const;
    const uint8_t *GetRaw() const { return m_data; }
    string Get() const;
    bool Blackout();
    void Reset();

  private:
    bool Init();
    bool DuplicateIfNeeded();
    void CopyFromOther(const DmxBuffer &other);
    void CleanupMemory();
    unsigned int *m_ref_count;
    mutable bool m_copy_on_write;
    uint8_t *m_data;
    unsigned int m_length;
};

} // lla
#endif
