
#include "SimpleProducer.h"

SimpleProducer::SimpleProducer()
{

}
SimpleProducer::~SimpleProducer()
{
	 	
	 	delete textMessage;
	 	cleanup();
}

void SimpleProducer::close()
{
	cleanup();
}

void SimpleProducer::start(const std::string& UserName, const std::string& Password, const std::string& brokerURI, unsigned int numMessages, const std::string& destURI, bool useTopic = false, bool clientAck = false)
{
	this->UserName = UserName;
	this->Password = Password;
	this->connection = NULL;
	this->session = NULL;
	this->destination = NULL;
	this->producer = NULL;
	this->numMessages = numMessages;
	this->useTopic = useTopic;
	this->brokerURI = brokerURI;
	this->destURI = destURI;
	this->clientAck = clientAck;

	initialize();
}

void SimpleProducer::initialize()
{
	try {
		// Create a ConnectionFactory                                         /////////////////////
		//ActiveMQConnectionFactory *connectionFactory = new ActiveMQConnectionFactory(brokerURI, UserName, Password);
		auto_ptr<ConnectionFactory> connectionFactory(ConnectionFactory::createCMSConnectionFactory(brokerURI));
		// Create a Connection
		try
		{
			connection = connectionFactory->createConnection();
			connection->start();
		}
		catch (CMSException& e)
		{
			e.printStackTrace();
			throw e;
		}

		// Create a Session
		if (clientAck) {
			session = connection->createSession(Session::CLIENT_ACKNOWLEDGE);
		}
		else {
			session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
		}

		// Create the destination (Topic or Queue)
		if (useTopic) {
			destination = session->createTopic(destURI);
		}
		else {
			destination = session->createQueue(destURI);
		}

		// Create a MessageProducer from the Session to the Topic or Queue
		producer = session->createProducer(destination);
		producer->setDeliveryMode(DeliveryMode::PERSISTENT);
	}
	catch (CMSException& e) {
		e.printStackTrace();
	}
}

void SimpleProducer::send(const char* Message, int nSize)
{
	// 消息内容
	//std::string threadIdStr = Long::toString( Thread::currentThread()->getId() );
	// 创建一个文本类型的消息
	if (session == nullptr)
		return;
	auto_ptr<BytesMessage> bytesMessage(session->createBytesMessage((unsigned char*)Message, nSize));
	// 发送消息
	//printf( "Sent message  from thread %s\n", threadIdStr.c_str() );
	producer->send(bytesMessage.get());

	////新家
	// 	delete bytesMessage;
	// 	cleanup();

	///
}


void SimpleProducer::cleanup()
{
	// Destroy resources.
	try {
		if (destination != NULL) delete destination;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	destination = NULL;

	try {
		if (producer != NULL) delete producer;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	producer = NULL;

	// Close open resources.
	try {
		if (session != NULL) session->close();
		if (connection != NULL) connection->close();
	}
	catch (CMSException& e) { e.printStackTrace(); }

	try {
		if (session != NULL) delete session;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	session = NULL;

	try {
		if (connection != NULL) delete connection;
	}
	catch (CMSException& e) { e.printStackTrace(); }
	connection = NULL;
}