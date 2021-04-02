#include "entity_manager.h"
#include "system.h"

void SystemInterface::Update()
{
  OnUpdate();

  /*
  TODO: �������� � ����� ���������� ������ � ���������� - ����� ����������� ���������. ��� ���� ������� ������ �� ���������, ������� �� ������� �����
  ����� ��������������� ���������, �� ������� ����� �������� ������������� ������� ������ ��� ��������������� ��������? ��������.
  */
  entityManager->ForEach([this](Entity* entity) 
  {
    if (Filter(entity)) //������� �������� � ������� ���������, �������� ������������ ����������� �������
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
