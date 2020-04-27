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


#include <algorithm>

#include "inet/common/ModuleAccess.h"
#include "inet/common/SelfDocumenterFingerprintCalculator.h"
#include "inet/common/packet/Message.h"
#include "inet/common/packet/Packet.h"

#ifdef __INET_SELFDOC_H

namespace inet {

Register_Class(SelfDocumenterFingerprintCalculator);

static TagSet *findTags(cMessage *msg)
{
    if (auto packet = dynamic_cast<Packet *>(msg))
        return &packet->getTags();
    if (auto message = dynamic_cast<Message *>(msg))
        return &message->getTags();
    return nullptr;
}

static std::string tagsToJson(const char *key, cMessage *msg)
{
    std::set<std::string> tagSet;
    std::ostringstream os;
    auto tags = findTags(msg);
    if (tags) {
        auto cnt = tags->getNumTags();
        for (int i=0; i < cnt; i++) {
            auto tag = tags->getTag(i);
            if (tag)
                tagSet.insert(opp_typename(typeid(*tag)));
        }
    }
    os << SelfDoc::val(key) << " : [ ";
    const char *sep = "";
    for (const auto& t : tagSet) {
        os << sep << SelfDoc::val(t);
        sep = ", ";
    }
    os << " ]";
    return os.str();
}

static std::string gateInfo(cGate *gate)
{
    if (gate) {
        std::ostringstream os;
        os << gate->getName() << (gate->isVector() ? "[]" : "");
        return os.str();
    }
    else
        return "<nullptr>";
}

static bool isNum (char c) { return (c >= '0' && c <= '9'); }

void SelfDocumenterFingerprintCalculator::addEvent(cEvent *event)
{
    if (event->isMessage()) {
        cMessage *msg = static_cast<cMessage *>(event);
        auto ctrl = msg->getControlInfo();
        auto context = msg->getContextPointer();

        auto from = msg->getSenderModule();
        if (msg->isSelfMessage()) {
            std::ostringstream os;
            std::string msgName = msg->getName();
            std::replace_if(msgName.begin(), msgName.end(), isNum, 'N');
            os << "=SelfDoc={ " << SelfDoc::keyVal("module", from->getComponentType()->getFullName())
                    << ", " << SelfDoc::keyVal("action", "SCHEDULE")
                    << ", " << SelfDoc::val("details") << " : {"
                    << SelfDoc::keyVal("msg", opp_typename(typeid(*msg)))
                    << ", " << SelfDoc::keyVal("kind", SelfDoc::kindToStr(msg->getKind(), from->getProperties(), "selfMessageKinds", nullptr, ""))
                    << ", " << SelfDoc::keyVal("ctrl", ctrl ? opp_typename(typeid(*ctrl)) : "<nullptr>")
                    << ", " << tagsToJson("tags", msg)
                    << ", " << SelfDoc::keyVal("msgname", msgName)
                    << ", " << SelfDoc::keyVal("context", context ? "filled" : "<nullptr>")
                    << " } }"
                   ;
            globalSelfDoc.insert(os.str());
        }
        else {
            auto senderGate = msg->getSenderGate();
            auto arrivalGate = msg->getArrivalGate();
            if (senderGate == nullptr) {
                std::ostringstream os;
                os << "=SelfDoc={ " << SelfDoc::keyVal("module", from->getComponentType()->getFullName())
                        << ", " << SelfDoc::keyVal("action", "OUTPUTDIRECT")
                        << ", " << SelfDoc::val("details") << " : {"
                        << SelfDoc::keyVal("msg", opp_typename(typeid(*msg)))
                        << ", " << SelfDoc::keyVal("kind", SelfDoc::kindToStr(msg->getKind(), from->getProperties(), "directSendKinds", arrivalGate->getProperties(), "messageKinds"))
                        << ", " << SelfDoc::keyVal("ctrl", ctrl ? opp_typename(typeid(*ctrl)) : "<nullptr>")
                        << ", " << tagsToJson("tags", msg)
                        << " } }"
                       ;
                globalSelfDoc.insert(os.str());
            }
            else {
                std::ostringstream os;
                os << "=SelfDoc={ " << SelfDoc::keyVal("module", from->getComponentType()->getFullName())
                        << ", " << SelfDoc::keyVal("action", "OUTPUT")
                        << ", " << SelfDoc::val("details") << " : {"
                        << SelfDoc::keyVal("gate", gateInfo(senderGate))
                        << ", "<< SelfDoc::keyVal("msg", opp_typename(typeid(*msg)))
                        << ", " << SelfDoc::keyVal("kind", SelfDoc::kindToStr(msg->getKind(), senderGate->getProperties(), "messageKinds", arrivalGate->getProperties(), "messageKinds"))
                        << ", " << SelfDoc::keyVal("ctrl", ctrl ? opp_typename(typeid(*ctrl)) : "<nullptr>")
                        << ", " << tagsToJson("tags", msg)
                        << " } }"
                       ;
                globalSelfDoc.insert(os.str());
            }

            {
                std::ostringstream os;
                auto to = msg->getArrivalModule();
                os << "=SelfDoc={ " << SelfDoc::keyVal("module", to->getComponentType()->getFullName())
                        << ", " << SelfDoc::keyVal("action", "INPUT")
                        << ", " << SelfDoc::val("details") << " : {"
                        << SelfDoc::keyVal("gate", gateInfo(arrivalGate))
                        << ", " << SelfDoc::keyVal("msg", opp_typename(typeid(*msg)))
                        << ", " << SelfDoc::keyVal("kind", SelfDoc::kindToStr(msg->getKind(), arrivalGate->getProperties(), "messageKinds", senderGate ? senderGate->getProperties() : nullptr, "messageKinds"))
                        << ", " << SelfDoc::keyVal("ctrl", ctrl ? opp_typename(typeid(*ctrl)) : "<nullptr>")
                        << ", " << tagsToJson("tags", msg)
                        << " } }"
                       ;
                globalSelfDoc.insert(os.str());
            }
        }
    }
    cSingleFingerprintCalculator::addEvent(event);
}

} // namespace

#endif // __INET_SELFDOC_H

