
#include "SimpleProducer.h"
#include<QMessageBox>
SimpleProducer::SimpleProducer()
{
	 connection = nullptr;
	 session = nullptr;
	 destination = nullptr;
	 producer = nullptr;
}
SimpleProducer::~SimpleProducer()
{
	 	cleanup();
}

void SimpleProducer::close()
{
	cleanup();
}


void SimpleProducer::onException(const CMSException& ex AMQCPP_UNUSED)
{
	printf("CMS Exception occurred.  Shutting down client.\n");
	exit(1);
}
bool SimpleProducer::start(const std::string& UserName, const std::string& Password, const std::string& brokerURI, unsigned int numMessages, const std::string& destURI, bool useTopic = false, bool clientAck = false)
{
	this->UserName = UserName;
	this->Password = Password;
	this->numMessages = numMessages;
	this->useTopic = useTopic;
	this->brokerURI = brokerURI;
	this->destURI = destURI;
	this->clientAck = clientAck;

	return initialize();
}

bool SimpleProducer::initialize()
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
		return true;
	}
	catch (CMSException& e) {
		e.printStackTrace();
		return false;
	}
}

LRESULT SimpleProducer::send(const char* Message, int nSize)
{
	try
	{
		// 消息内容
		// 创建一个文本类型的消息
		if (session == nullptr)
			return -1;
		BytesMessage* bytesMessage=session->createBytesMessage((unsigned char*)Message, nSize);
		// 发送消息
		producer->send(bytesMessage);
		delete bytesMessage;
		return 1;
	}
	catch (CMSException& e)
	{
		return -1;
	}
	
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