#pragma once

#include <memory>

class SceneManager;

class SceneInterface
{
  friend class SceneManager;
  SceneManager* sceneManager;

 public:
	 SceneManager* GetSceneManager() const {
		 return sceneManager;
	 };
  virtual void OnCreate() {};
  virtual void OnUpdate() {};
  virtual void OnDispose() {};
  virtual ~SceneInterface() = default;
};