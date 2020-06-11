//
// Copyright (C) OpenSim Ltd.
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
// along with this program; if not, see http://www.gnu.org/licenses/.
//

#include "inet/common/ProtocolTag_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/protocol/ethernet/EthernetFcsChecker.h"

namespace inet {

Define_Module(EthernetFcsChecker);

void EthernetFcsChecker::initialize(int stage)
{
    FcsCheckerBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        popFcs = par("popFcs");
}

bool EthernetFcsChecker::checkFcs(const Packet *packet, FcsMode fcsMode, uint32_t fcs) const
{
    switch (fcsMode) {
        case FCS_DECLARED_CORRECT:
            return checkDeclaredCorrectFcs(packet, fcs);
        case FCS_DECLARED_INCORRECT:
            return checkDeclaredIncorrectFcs(packet, fcs);
        case FCS_COMPUTED:
            return checkComputedFcs(packet, fcs);
        default:
            throw cRuntimeError("Unknown FCS mode");
    }
}

void EthernetFcsChecker::processPacket(Packet *packet)
{
    if (popFcs) {
        const auto& trailer = packet->popAtBack<EthernetFcs>(ETHER_FCS_BYTES);
        auto& packetProtocolTag = packet->getTagForUpdate<PacketProtocolTag>();
        packetProtocolTag->setBackOffset(packetProtocolTag->getBackOffset() + trailer->getChunkLength());
    }
}

bool EthernetFcsChecker::matchesPacket(const Packet *packet) const
{
    const auto& trailer = packet->peekAtBack<EthernetFcs>(ETHER_FCS_BYTES);
    auto fcsMode = trailer->getFcsMode();
    auto fcs = trailer->getFcs();
    return checkFcs(packet, fcsMode, fcs);
}

void EthernetFcsChecker::dropPacket(Packet *packet)
{
    PacketFilterBase::dropPacket(packet, INCORRECTLY_RECEIVED);
}

} // namespace inet

