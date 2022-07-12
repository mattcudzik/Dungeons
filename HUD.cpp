#include "HUD.h"

std::vector<sf::Sprite> HUD::m_hearts; 
sf::Text HUD::m_text;
sf::Font HUD::m_font;
sf::RectangleShape HUD::m_messageBackground;
sf::Text HUD::m_messageTextMain;
sf::Text HUD::m_messageTextSec;
bool HUD::waitForEnter = false;
HUD::HUD()
{
	UpdateHealthPoints();
	
	m_font.loadFromFile("Textures/PixeloidSans.ttf");
	m_text = sf::Text();
	m_text.setFont(m_font);
	m_text.setString("Level: 1");
	m_text.setCharacterSize(16 * Tools::scale);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(sf::Vector2f(8 * Tools::scale, 8 * Tools::scale));
	
}
void HUD::Draw(sf::RenderWindow& window)
{
	for (auto sprite : HUD::m_hearts)
	{
		window.draw(sprite);
	}
	window.draw(m_text);
	window.draw(m_messageBackground);
	window.draw(m_messageTextMain);
	window.draw(m_messageTextSec);
}
void HUD::UpdateHealthPoints()
{
	std::shared_ptr<Entity> player = LevelHandler::Instance().GetCurrentLevel()->player;
	if (player->HasComponent(Component::ComponentType::Health))
	{
		m_hearts.clear();

		std::shared_ptr<HealthComp> healthComp = std::dynamic_pointer_cast<HealthComp>(player->GetComponent(Component::ComponentType::Health));
		std::shared_ptr<sf::Texture> texture = TextureHandler::Instance().getTexture(TextureHandler::Heart);
		
		int screeenWidth = Level::width * Level::tileSize * Tools::scale;
		int allHearts = healthComp->GetMaxHealth() / 2;

		if (healthComp->GetMaxHealth() % 2 == 1)
			allHearts++;
		if (allHearts > 50)
			allHearts = 50;

		int fullHearts = healthComp->GetCurrenHealth() / 2;
		int emptyHearts = (healthComp->GetMaxHealth() - healthComp->GetCurrenHealth()) / 2;
		bool isHalfHeart = healthComp->GetCurrenHealth() % 2 == 1;

		for (int i = 0; i < allHearts; i++)
		{
			sf::Sprite tmp;

			if (i < emptyHearts)
				tmp = sf::Sprite(*texture, sf::IntRect(32, 0, 16, 16));
			else if(i== emptyHearts && isHalfHeart)
				tmp = sf::Sprite(*texture, sf::IntRect(16, 0, 16, 16));
			else if(i<=fullHearts+emptyHearts)
				tmp = sf::Sprite(*texture, sf::IntRect(0, 0, 16, 16));

			tmp.setPosition(sf::Vector2f(screeenWidth - (i + 2) * 16 * Tools::scale, 8 * Tools::scale));
			tmp.setScale(sf::Vector2f(Tools::scale, Tools::scale));
			m_hearts.push_back(tmp);
		}
	}
}

void HUD::UpdateCurrentLevel(int level)
{
	m_text.setString("Level: " + std::to_string(level));
}

void HUD::ShowMessage()
{
	float scale = Tools::scale;
	m_messageBackground.setFillColor(sf::Color(0, 0, 0, 200));
	m_messageBackground.setPosition(sf::Vector2f(16 * 4 * scale, 4 * 16 * scale));
	m_messageBackground.setSize(sf::Vector2f(16 * 12 * scale, 16 * 8 * scale));
	
	m_messageTextMain.setFont(m_font);
	m_messageTextMain.setString("You Died!");
	m_messageTextMain.setFillColor(sf::Color::White);
	m_messageTextMain.setCharacterSize(32 * scale);
	m_messageTextMain.setPosition(m_messageBackground.getPosition() - sf::Vector2f(m_messageTextMain.getGlobalBounds().width / 2, 0) + sf::Vector2f(m_messageBackground.getGlobalBounds().width / 2, 16 * scale));
	
	m_messageTextSec.setFont(m_font);
	m_messageTextSec.setString("Press Enter\n to continue...");
	m_messageTextSec.setFillColor(sf::Color::White);
	m_messageTextSec.setCharacterSize(16 * scale);
	m_messageTextSec.setPosition(m_messageBackground.getPosition() - sf::Vector2f(m_messageTextSec.getGlobalBounds().width / 2, 0) + sf::Vector2f(m_messageBackground.getGlobalBounds().width / 2, 16 * scale * 4));


}
void HUD::HideMessage()
{
	m_messageBackground.setSize(sf::Vector2f(0, 0));
	m_messageTextMain.setCharacterSize(0);
	m_messageTextSec.setCharacterSize(0);
}