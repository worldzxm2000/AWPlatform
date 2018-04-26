/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ACTIVEMQ_COMMANDS_JOURNALTOPICACK_H_
#define _ACTIVEMQ_COMMANDS_JOURNALTOPICACK_H_

// Turn off warning message for ignored exception specification
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include <activemq/commands/ActiveMQDestination.h>
#include <activemq/commands/BaseDataStructure.h>
#include <activemq/commands/MessageId.h>
#include <activemq/commands/TransactionId.h>
#include <activemq/util/Config.h>
#include <decaf/lang/Pointer.h>
#include <string>
#include <vector>

namespace activemq {
namespace commands {

    using decaf::lang::Pointer;

    /*
     *
     *  Command code for OpenWire format for JournalTopicAck
     *
     *  NOTE!: This file is auto generated - do not modify!
     *         if you need to make a change, please see the Java Classes
     *         in the activemq-cpp-openwire-generator module
     *
     */
    class AMQCPP_API JournalTopicAck : public BaseDataStructure {
    protected:

        Pointer<ActiveMQDestination> destination;
        Pointer<MessageId> messageId;
        long long messageSequenceId;
        std::string subscritionName;
        std::string clientId;
        Pointer<TransactionId> transactionId;

    public:

        const static unsigned char ID_JOURNALTOPICACK = 50;

    private:

        JournalTopicAck(const JournalTopicAck&);
        JournalTopicAck& operator= (const JournalTopicAck&);

    public:

        JournalTopicAck();

        virtual ~JournalTopicAck();

        virtual unsigned char getDataStructureType() const;

        virtual JournalTopicAck* cloneDataStructure() const;

        virtual void copyDataStructure(const DataStructure* src);

        virtual std::string toString() const;

        virtual bool equals(const DataStructure* value) const;

        virtual const Pointer<ActiveMQDestination>& getDestination() const;
        virtual Pointer<ActiveMQDestination>& getDestination();
        virtual void setDestination( const Pointer<ActiveMQDestination>& destination );

        virtual const Pointer<MessageId>& getMessageId() const;
        virtual Pointer<MessageId>& getMessageId();
        virtual void setMessageId( const Pointer<MessageId>& messageId );

        virtual long long getMessageSequenceId() const;
        virtual void setMessageSequenceId( long long messageSequenceId );

        virtual const std::string& getSubscritionName() const;
        virtual std::string& getSubscritionName();
        virtual void setSubscritionName( const std::string& subscritionName );

        virtual const std::string& getClientId() const;
        virtual std::string& getClientId();
        virtual void setClientId( const std::string& clientId );

        virtual const Pointer<TransactionId>& getTransactionId() const;
        virtual Pointer<TransactionId>& getTransactionId();
        virtual void setTransactionId( const Pointer<TransactionId>& transactionId );

    };

}}

#endif /*_ACTIVEMQ_COMMANDS_JOURNALTOPICACK_H_*/
