#include "AnimationManager.h"
#include "Sprite.h"
#include "Frame.h"
#include "../TinyXML/tinyxml.h"
#include "../SGD Wrappers/SGD_Geometry.h"
#include "../SGD Wrappers/SGD_GraphicsManager.h"

/*static*/ AnimationManager* AnimationManager::s_pInstance = nullptr;

/*static*/ AnimationManager* AnimationManager::GetInstance()
{
	if (s_pInstance == nullptr)
		s_pInstance = new AnimationManager;
	return s_pInstance;
}


/*static*/ void AnimationManager::DeleteInstance()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


// LoadSprites
//	- reading all the sprites from the XML file
std::string AnimationManager::LoadSprites(std::string fileName)
{
	TiXmlDocument animationDoc;

	// Check to see if there is anything to load from the file
	if (animationDoc.LoadFile(fileName.c_str()) == false)
		return false;

	Sprite* newSprite = new Sprite();
	TiXmlElement* root = animationDoc.RootElement();
	
	// Check to see if there is actually anything to read in the XML
	if (root == nullptr)
		return false;
	// Getting rid of any past data
	m_mSprites.clear();

	std::string ID;
	TiXmlElement* spriteImg = root->FirstChildElement("sprite");
	while (spriteImg != nullptr)
	{
		if (spriteImg != nullptr)
		{
			std::string file = "resource/animation/";
			file += spriteImg->GetText();

			if (file.c_str() != nullptr)
				newSprite->SetImage(file.c_str());
		}
		spriteImg = spriteImg->NextSiblingElement("spriteID");
		if (spriteImg != nullptr)
		{
			std::string id = spriteImg->GetText();
			if (id.c_str() != nullptr)
			{
				newSprite->SetSpriteID(id);
				ID = id;
			}
		}
		spriteImg = spriteImg->NextSiblingElement("isLooping");
		if (spriteImg != nullptr)
		{
			int boolNum;
			spriteImg->Attribute("isIt", &boolNum);
			if (boolNum == 0)
				newSprite->SetLooping(false);
			else
				newSprite->SetLooping(true);

		}
		TiXmlElement* frames = spriteImg->NextSiblingElement("frame");
		while (frames != nullptr)
		{
			frames = frames->FirstChildElement("collisionRect");
			Frame* newFrame = new Frame();
			if (frames != nullptr)
			{
				SGD::Rectangle collTemp;
				double l, t, r, b;
				frames->Attribute("left", &l);
				collTemp.left = (float)l;
				frames->Attribute("right", &r);
				collTemp.right = (float)r;
				frames->Attribute("top", &t);
				collTemp.top = (float)t;
				frames->Attribute("bottom", &b);
				collTemp.bottom = (float)b;

				newFrame->SetCollisionRect(collTemp);
			}

			frames = frames->NextSiblingElement("drawRect");
			if (frames != nullptr)
			{
				SGD::Rectangle drawTemp;
				double l, t, r, b;
				frames->Attribute("left", &l);
				drawTemp.left = (float)l;
				frames->Attribute("right", &r);
				drawTemp.right = (float)r;
				frames->Attribute("top", &t);
				drawTemp.top = (float)t;
				frames->Attribute("bottom", &b);
				drawTemp.bottom = (float)b;

				newFrame->SetFrameRect(drawTemp);
			}

			frames = frames->NextSiblingElement("duration");
			if (frames != nullptr)
			{
				double durtemp;
				frames->Attribute("time", &durtemp);
				newFrame->SetDuration((float)durtemp);

			}

			frames = frames->NextSiblingElement("anchorPoint");
			if (frames != nullptr)
			{
				SGD::Point pointTemp;
				double x, y;
				frames->Attribute("X", &x);
				pointTemp.x = (float)x;
				frames->Attribute("Y", &y);
				pointTemp.y = (float)y;
				newFrame->SetAnchorPoint(pointTemp);
			}

			frames = frames->NextSiblingElement("triggerID");
			if (frames != nullptr)
			{
				std::string trigid = frames->GetText();
				if (trigid.c_str() != nullptr)
					newFrame->SetTriggerID(trigid);
			}
			newSprite->AddFrame(newFrame);
			frames = frames->FirstChildElement("frames");
		}
		m_mSprites[newSprite->GetSpriteID()] = newSprite;
		m_vSpriteNames.push_back(newSprite->GetSpriteID());
		//m_vSprites.push_back(newSprite);
		spriteImg = spriteImg->NextSiblingElement("sprite");
	}
	if (m_mSprites.size() > 0)
		return ID;
	else
		return nullptr;
}

void AnimationManager::UnloadSprites()
{
	//for (size_t i = 0; i < m_vSprites.size(); i++)
	//{
	//	delete m_vSprites[i];
	//	m_vSprites[i] = nullptr;
	//}

	for (unsigned int i = 0; i < m_mSprites.size(); i++)
	{
		delete m_mSprites[m_vSpriteNames[i]];
	}
}


void AnimationManager::Update(AnimationTimestamp& ants, float dt)
{
	ants.m_fTimeOnFrame += dt;
	// check to see if the frame duration is over
	if (ants.m_fTimeOnFrame > m_mSprites[ants.m_nCurrAnimation]->GetFrame(ants.m_nCurrFrame).GetDuration())
	{
		ants.m_fTimeOnFrame -= m_mSprites[ants.m_nCurrAnimation]->GetFrame(ants.m_nCurrFrame).GetDuration();

		// change to next frame
		++ants.m_nCurrFrame;

		// check to see if its the last frame
		if (ants.m_nCurrFrame == m_mSprites[ants.m_nCurrAnimation]->GetFrameSize())
		{
			// if they are looping they will go back to the first frame
			if (m_mSprites[ants.m_nCurrAnimation]->IsLooping())
				ants.m_nCurrFrame = 0;
			else
			{
				// if not stop at the last frame
				--ants.m_nCurrFrame;
			}
		}
	}
}

void AnimationManager::Render(AnimationTimestamp& ants, float x, float y)
{
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(m_mSprites[ants.m_nCurrAnimation]->GetImage(),
	{ (float)x, (float)y },
	m_mSprites[ants.m_nCurrAnimation]->GetFrame(ants.m_nCurrFrame).GetFrameRect());

}


Sprite* AnimationManager::GetSprite(std::string nameID)
{
	if (m_mSprites[nameID] != nullptr)
		return m_mSprites[nameID];
	else
		return nullptr;
}
