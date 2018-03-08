//
// Copyright (C) 2003 Andras Varga; CTIE, Monash University, Australia
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

import inet.common.INETDefs;
import inet.physicallayer.common.packetlevel.WiredSignal;

cplusplus {{
#include "inet/linklayer/ethernet/Ethernet.h"
}}

namespace inet;

//
// Abstract base class for various Ethernet traffic types:
// EtherJam, EtherFilledIfg and EtherPhyFrame.
//
class EthernetSignal extends inet::physicallayer::WiredSignal
{
}

//
// Represents jam on the Ethernet.
//
class EthernetJamSignal extends EthernetSignal
{
    long abortedPkTreeID = 0;  // this field stores the packetTreeId of the aborted packet
}

//
// Represents a filled inter-frame gap in burst mode.
// Also used for calculating IFG times.
//
class EthernetFilledIfgSignal extends EthernetSignal
{
    bitLength = INTERFRAME_GAP_BITS;
}
