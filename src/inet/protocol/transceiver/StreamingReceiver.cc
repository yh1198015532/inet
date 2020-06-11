//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "inet/protocol/transceiver/StreamingReceiver.h"

namespace inet {

Define_Module(StreamingReceiver);

void StreamingReceiver::initialize(int stage)
{
    PacketReceiverBase::initialize(stage);
    OperationalMixin::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        datarate = bps(par("datarate"));
}

StreamingReceiver::~StreamingReceiver()
{
    delete rxSignal;
}

void StreamingReceiver::handleMessageWhenUp(cMessage *message)
{
    if (message->getArrivalGate() == inputGate)
        receiveFromMedium(message);
    else
        PacketReceiverBase::handleMessage(message);
}

void StreamingReceiver::handleMessageWhenDown(cMessage *msg)
{
    if (!msg->isSelfMessage()) {
        // received on input gate from another network node
        EV << "Interface is turned off, dropping message (" << msg->getClassName() << ")" << msg->getName() << "\n";
        delete msg;
    }
    else
        OperationalMixin::handleMessageWhenDown(msg);
}

void StreamingReceiver::sendToUpperLayer(Packet *packet)
{
    pushOrSendPacket(packet, outputGate, consumer);
}

void StreamingReceiver::receivePacketStart(cPacket *cpacket, cGate *gate, double datarate)
{
    ASSERT(rxSignal == nullptr);
    take(cpacket);
    rxSignal = check_and_cast<Signal *>(cpacket);
}

void StreamingReceiver::receivePacketProgress(cPacket *cpacket, cGate *gate, double datarate, int bitPosition, simtime_t timePosition, int extraProcessableBitLength, simtime_t extraProcessableDuration)
{
    take(cpacket);
    if (rxSignal) {
        delete rxSignal;
        rxSignal = check_and_cast<Signal *>(cpacket);
    }
    else {
        EV_WARN << "Signal start doesn't received, drop it";
        delete cpacket;
    }
}

void StreamingReceiver::receivePacketEnd(cPacket *cpacket, cGate *gate, double datarate)
{
    take(cpacket);
    auto signal = check_and_cast<Signal *>(cpacket);
    if (rxSignal) {
        delete rxSignal;
        rxSignal = nullptr;
        auto packet = decodePacket(signal);
        sendToUpperLayer(packet);
        delete signal;
    }
    else {
        EV_WARN << "Signal start doesn't received, drop it";
        //TODO drop signal
        delete signal;
    }
}

void StreamingReceiver::handleStartOperation(LifecycleOperation *operation)
{
}

void StreamingReceiver::handleStopOperation(LifecycleOperation *operation)
{
    delete rxSignal;
    rxSignal = nullptr;
}

void StreamingReceiver::handleCrashOperation(LifecycleOperation *operation)
{
    delete rxSignal;
    rxSignal = nullptr;
}

} // namespace inet

