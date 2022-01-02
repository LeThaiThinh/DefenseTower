#pragma once
class BountyObject
{
public:
	BountyObject() :m_bounty(0) {}
	BountyObject(int bounty):m_bounty(bounty){}
	~BountyObject(){}

	int GetBounty() { return m_bounty; }
protected:
	int m_bounty;
};
