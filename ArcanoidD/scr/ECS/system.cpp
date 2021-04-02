#include "entity_manager.h"
#include "system.h"

void SystemInterface::Update()
{
  OnUpdate();

  /*
  TODO: проверка и потом применение систем к компонетам - самая туродоемкая процедура. Что если создать вектор из сущностей, какждая их которых будет
  иметь соответствующие компонеты, на которые будет вызывать универсальная функция систем без предварительной проверки? Подумать.
  */
  entityManager->ForEach([this](Entity* entity) 
  {
    if (Filter(entity)) //Найдена сущность с нужными условиями, вызываем определенную виртуальную функцию
		Update(entity);
  });

  OnPostUpdate();
}

bool SystemInterface::Filter(Entity* entity) const
{
  return true;
}

EntityManager* SystemInterface::GetEntityManager()
{
  return entityManager;
}
