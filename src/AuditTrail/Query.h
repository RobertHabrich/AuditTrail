#pragma once

#include "Message.h"
#include "Event.h"
#include "ActiveParticipant.h"

namespace AuditTrail
{

/*!
    Describes the event of a Query being issued or received.
    The message does not record the response to the query, but merely records the fact that a query
    was issued. For example, this would issue queries using the DICOM SOP Classes:

    * Modality Worklist
    * UPS Pull
    * UPS Watch
    * Composite Instance Query

    \note   The response to a query may result in one or more InstancesTransferred or
            InstancesAccessed messages, depending on what events transpired after the query.
            If there were security-related failures, such as access violations, when processing a
            query, those failues should show up in other audit messages, such as a Security Alert
            message.

    \note   Non-DICOM queries may also be captured by this message. The Participant Object ID Type
            Code, the Participant Object ID, and the Query fields may have values related to such
            non-DICOM queries.

    \todo   ParticipantObjectDetail is MC, but EntityParticipantObject does not support it yet.
*/
class Query : public Message
{
public:
    Query(Outcome outcome, ActiveParticipant queryingProcess, ActiveParticipant queriedProcess,
          std::string queriedSOPClassUID, std::string base64Dataset);

    std::vector<IO::Node> createNodes() const override;

    /*! Other participants that are known, especially third parties that requested the query */
    void addOtherParticipant(ActiveParticipant otherParticipant);

private:
    Outcome m_outcome;
    ActiveParticipant m_queryingProcess;
    ActiveParticipant m_queriedProcess;
    std::string m_queriedSOPClassUID;
    std::string m_base64Dataset;
    std::vector<ActiveParticipant> m_otherParticipants;
};

}
