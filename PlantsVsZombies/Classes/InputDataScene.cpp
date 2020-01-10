#include "InputDataScene.h"
#include "GlobalVariable.h"

#define FontSize 20

Scene* InputDataMenu::CreateInputDataScene()
{
	return InputDataMenu::create();
}

bool InputDataMenu::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->CreateBackGroundImage();

	this->CreateDialogs();

	return true;
}

void InputDataMenu::CreateDialogs()
{
	DataButton.clear();

	CaveFileDialog = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(global->ImagesPath.find("InputDataDialog")->second));
	CaveFileDialog->setPosition(Director::getInstance()->getWinSize() / 2);
	CaveFileDialog->setScale(2.0f);
	CaveFileDialog->setName("CaveFileDialog");
	this->addChild(CaveFileDialog);

	auto question = Label::createWithTTF("ѡ����Ĵ浵", "resources/fonts/fzse_gbk.ttf", 30);
	question->setTextColor(Color4B::YELLOW);
	question->setPosition(Vec2(CaveFileDialog->getContentSize().width / 2, CaveFileDialog->getContentSize().height - 110));
	CaveFileDialog->addChild(question);

	auto SeedPacketSilhouette1 = Sprite::create(global->ImagesPath.find("SeedPacketSilhouette1")->second);
	SeedPacketSilhouette1->setPosition(Vec2(245, 270));
	SeedPacketSilhouette1->setScale(2.0f);
	CaveFileDialog->addChild(SeedPacketSilhouette1);

	for (int i = 0; i < 8; i++)
	{
		this->CreateDataButton(CaveFileDialog, global->UserData.UserCaveFileName[i], Vec2(245, 357 - 25 * i), 3.7f, i);
	}

	/* if not read data, read it */
	if (global->UserGameData.UserDataNumber == -1)
	{
		CaveFileNumber = UserDefault::getInstance()->getIntegerForKey("USERDATANUMBER");
		DataButton.find(CaveFileNumber)->second->setColor(Color3B::YELLOW);
	}
	else
	{
		CaveFileNumber = global->UserGameData.UserDataNumber;
		DataButton.find(global->UserGameData.UserDataNumber)->second->setColor(Color3B::YELLOW);
	}

	/* ������ť */
	this->CreateButtons(CaveFileDialog, global->GameText.find("ȷ��")->second, Vec2(110, 70), 1.0f, 3);
	this->CreateButtons(CaveFileDialog, global->GameText.find("ȡ��")->second, Vec2(245, 70), 1.0f, 4);
	this->CreateButtons(CaveFileDialog, global->GameText.find("������")->second, Vec2(380, 70), 1.0f, 5);

	/* �������� */
	this->CreateTouchtListener(CaveFileDialog);
}

void InputDataMenu::CreateInputDialog()
{
	InputDataDialog = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(global->ImagesPath.find("QuitDialog")->second));
	InputDataDialog->setPosition(Director::getInstance()->getWinSize() / 2);
	InputDataDialog->setScale(3.0f);
	InputDataDialog->setName("InputDataDialog");
	this->addChild(InputDataDialog);

	auto editbox = Sprite::create(global->ImagesPath.find("editbox")->second);
	editbox->setPosition(Vec2(155, 140));
	editbox->setScale(0.7f);
	InputDataDialog->addChild(editbox);

	InputCursor = Sprite::create(global->ImagesPath.find("InputCursor")->second);
	InputCursor->setScale(0.7f);
	InputCursor->setPosition(Vec2(155, 140));
	InputCursor->setVisible(false);
	InputDataDialog->addChild(InputCursor);
	InputCursor->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.25f), FadeIn::create(0.25f), nullptr)));

	_textField = TextField::create("����˴���������","resources/fonts/GameFont.ttf", FontSize);
	InputDataDialog->addChild(_textField);
	_textField->setPosition(Vec2(155, 137));
	_textField->setMaxLengthEnabled(true);
	_textField->setMaxLength(10);
	_textField->addEventListener([=](Ref* ref, TextField::EventType type)
		{
			switch (type)
			{
			case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
				_textField->setPlaceHolder(" ");
				InputCursor->setVisible(true);
				break;
			case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
				_textField->setPlaceHolder("����˴���������");
				InputCursor->setVisible(false);
				break;
			case cocos2d::ui::TextField::EventType::INSERT_TEXT:
			{
				/* ��ȡ�����ӵ��ַ� */
				newInputstring = _textField->getString().substr(InputString.size());

				/* �����ַ��� */
				InputString = _textField->getString();

				/* �����ַ����� */
				auto textLabel = onTextFieldInsertText();
				
				InputCursor->setPositionX(InputCursor->getPositionX() + textLabel->getContentSize().width / 2);
			}
				
				break;
			case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
			{
				/* ��ȡɾ�����ַ� */
				newInputstring = InputString.substr(_textField->getString().size());

				/* �����ַ��� */
				InputString = _textField->getString();

				/* ɾ������ */
				auto textLabel = onTextFieldDeleteBackward();

				InputCursor->setPositionX(InputCursor->getPositionX() - textLabel->getContentSize().width / 2);
			}
				break;
			default:
				break;
			}
		});

	/* ������ť */
	this->CreateButtons(InputDataDialog, global->GameText.find("ȷ��")->second, Vec2(90, 65),1.0f, 1);
	this->CreateButtons(InputDataDialog, global->GameText.find("ȡ��")->second, Vec2(225, 65),1.0f, 2);
	
	/* �������� */
	this->CreateTouchtListener(InputDataDialog);
}


void InputDataMenu::CreateButtons(Sprite* sprite, const std::string &Label, Vec2 &vec2,const float& scale, const int& ID)
{
	auto button = Button::create(global->ImagesPath.find("button")->second, global->ImagesPath.find("button_down")->second);
	button->setPosition(vec2);
	button->setScaleX(scale);
	button->setTitleLabel(label(Label, 20, Vec2(0, 0), 0, Color3B::GREEN, 1.0f/scale));
	sprite->addChild(button);

	button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::BEGAN:
			AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
			break;
		case Widget::TouchEventType::ENDED:
			switch (ID)
			{
			case 1: /* ȷ�� */
				if (strlen(_textField->getString().c_str()))
				{
					global->UserData.UserName = _textField->getString();
					UserDefault::getInstance()->setStringForKey(global->UserData.UserCaveFileNameKey[CaveFileNumber].c_str(), global->UserData.UserName);
					global->UserData.IsUpdate = true;

					global->UserData.UserCaveFileName[CaveFileNumber] = global->UserData.UserName;
				}
				CreateDialogs();
				this->removeChildByName("InputDataDialog");
				break;
			case 2: /* ȡ�� */
				CreateDialogs();
				this->removeChildByName("InputDataDialog");
				break;
			case 3:
				UserDefault::getInstance()->setIntegerForKey("USERDATANUMBER", CaveFileNumber); /* ��¼��ѡ�浵 */
				global->UserGameData.UserDataNumber = CaveFileNumber;

				/* ��ȡ��ѡ�浵�����ֲ����� */
				if (UserDefault::getInstance()->getStringForKey(global->UserData.UserCaveFileNameKey[global->UserGameData.UserDataNumber].c_str()) != "")
				{
					global->UserData.UserName = UserDefault::getInstance()->getStringForKey(global->UserData.UserCaveFileNameKey[global->UserGameData.UserDataNumber].c_str());
				}
				else
				{
					global->UserData.UserName = global->UserData.UserCaveFileName[CaveFileNumber];
				}
				global->UserData.IsUpdate = true;

				Director::getInstance()->popScene();
				break;
			case 4:
				Director::getInstance()->popScene();
				break;
			case 5:
				global->UserGameData.UserDataNumber = CaveFileNumber;
				this->removeChildByName("CaveFileDialog");
				CreateInputDialog();
				break;
			}
		}
	});
}

void InputDataMenu::CreateDataButton(Sprite* sprite, const std::string& Labels, Vec2& vec2, const float& scale, const int& ID)
{
	auto button = Button::create(global->ImagesPath.find("CaveFileButton")->second, global->ImagesPath.find("CaveFileButtonDown")->second);
	button->setPosition(vec2);
	button->setScale9Enabled(true);
	button->setScaleX(scale);
	auto label = Label::createWithTTF(Labels, "resources/fonts/GameFont.ttf", 17);
	label->setColor(Color3B::BLACK);
	label->setScaleX(1.0f / scale);
	button->setTitleLabel(label);
	sprite->addChild(button);

	DataButton.insert(pair<int, Button*>(ID, button));

	button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type)
		{
			switch (type)
			{
			case Widget::TouchEventType::BEGAN:
				AudioEngine::setVolume(AudioEngine::play2d(global->MusicsPath.find("gravebutton")->second), global->GlobalMusic.SoundEffect);
				break;
			case Widget::TouchEventType::ENDED:
				CaveFileNumber = ID;
				switch (ID)
				{
				case 0:
					SetButtonColor(button);
					break;
				case 1:
					SetButtonColor(button);
					break;
				case 2:
					SetButtonColor(button);
					break;
				case 3:
					SetButtonColor(button);
					break;
				case 4:
					SetButtonColor(button);
					break;
				case 5:
					SetButtonColor(button);
					break;
				case 6:
					SetButtonColor(button);
					break;
				case 7:
					SetButtonColor(button);
					break;
				}
			}
		});
}

void InputDataMenu::SetButtonColor(Button* button)
{
	for (auto sp : DataButton)
	{
		sp.second->setColor(Color3B::WHITE);
	}
	button->setColor(Color3B::YELLOW);
}

Label* InputDataMenu::onTextFieldInsertText()
{
	auto textLabel = Label::createWithTTF(newInputstring, "resources/fonts/GameFont.ttf", FontSize);
	textLabel->setColor(Color3B(0, 255, 255));
	textLabel->setName("label");
	InputDataDialog->addChild(textLabel);

	auto endPos = InputCursor->getPosition() - Vec2(0, 5);
	auto inputTextSize = textLabel->getContentSize();
	Vec2 beginPos(endPos.x + textLabel->getContentSize().width / 2, 270);

	float duration = 0.5f;
	textLabel->setPosition(beginPos);
	textLabel->setScale(8);

	auto seq = Sequence::create(
		Spawn::create(
			MoveTo::create(duration, endPos),
			ScaleTo::create(duration, 1),
			FadeOut::create(duration),
			nullptr),
		CallFunc::create([=]()
			{
				InputDataDialog->removeChildByName("label");
			}), nullptr);
	textLabel->runAction(seq);

	return textLabel;
}

Label* InputDataMenu::onTextFieldDeleteBackward()
{
	// create a delete text sprite and do some action
	auto label = Label::createWithTTF(newInputstring, "resources/fonts/GameFont.ttf", FontSize);
	label->setName("label");
	label->setColor(Color3B::YELLOW);
	InputDataDialog->addChild(label);

	// move the sprite to fly out
	auto beginPos = InputCursor->getPosition();
	auto textfieldSize = InputCursor->getContentSize();
	auto labelSize = label->getContentSize();
	beginPos.x += (textfieldSize.width - labelSize.width) / 2.0f;

	auto winSize = Director::getInstance()->getWinSize();
	Vec2 endPos(-winSize.width / 4.0f, winSize.height / 2.0f * (0.25 + (float)rand() / (2.0f * RAND_MAX)));

	float duration = 1;
	float rotateDuration = 0.35f;
	int repeatTime = 5;
	label->setPosition(beginPos);

	auto seq = Sequence::create(
		Spawn::create(
			MoveTo::create(duration, endPos),
			Repeat::create(
				RotateBy::create(rotateDuration, (rand() % 2) ? 360 : -360),
				repeatTime),
			FadeOut::create(duration),
			nullptr),
		CallFunc::create([=]() 
			{
				InputDataDialog->removeChildByName("label");
			}),
		nullptr);
	label->runAction(seq);

	return label;
}
