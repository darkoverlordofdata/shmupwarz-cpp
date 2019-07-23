/* ******************************************************************************
 * Copyright 2019 darkoverlordofdata.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/
#pragma once

/**
 * Artemis Revisited
 * 
 * I'm going with a header only library - I have trouble reasoning about code 
 * when there are header and impl files to deal with - it's what I hate most about c++.
 * 
 * I've gone back to the definitions in the original java version,via my vala port. 
 * c++17 has lots of new features, so the util folder is deprecated.
 */

#define BITSIZE 32
/**
 * TypeOf
 * 
 * wrapper around the type_info& object
 * c++ has no typeof operator, so we'll make our own:
 */
#define typeof(x) std::type_index(typeid(x))


#include "Core/IType.hpp"
#include "Core/IComponent.hpp"
#include "Core/IEntity.hpp"
#include "Core/IWorld.hpp"
#include "Core/IFactory.hpp"
#include "Core/IManager.hpp"
#include "Core/IPooledComponent.hpp"
#include "Core/IComponentPool.hpp"
#include "Core/IComponentManager.hpp"
#include "Core/IComponentMapper.hpp"
#include "Core/IComponentType.hpp"
#include "Core/IComponentTypeFactory.hpp"
#include "Core/IEntityManager.hpp"
#include "Core/IEntityObserver.hpp"
#include "Core/IEntitySystem.hpp"
#include "Core/IAspect.hpp"
#include "Managers/IGroupManager.hpp"
#include "Managers/IPlayerManager.hpp"
#include "Managers/ITagManager.hpp"
#include "Managers/ITeamManager.hpp"
#include "Systems/IDelayedEntityProcessingSystem.hpp"
#include "Systems/IEntityProcessingSystem.hpp"
#include "Systems/IIntervalEntityProcessingSystem.hpp"
#include "Systems/IIntervalEntitySystem.hpp"
#include "Systems/IVoidEntitySystem.hpp"

#include "Core/Type.hpp"
#include "Core/Component.hpp"
#include "Core/ComponentType.hpp"
#include "Core/ComponentTypeFactory.hpp"
#include "Core/EntityManager.hpp"
#include "Core/ComponentManager.hpp"
#include "Core/EntitySystem.hpp"
#include "Core/World.hpp"
#include "Core/Entity.hpp"
#include "Core/PooledComponent.hpp"
#include "Core/ComponentPool.hpp"
#include "Core/ComponentMapper.hpp"
#include "Core/Aspect.hpp"
#include "Core/Factory.hpp"
#include "Managers/GroupManager.hpp"
#include "Managers/PlayerManager.hpp"
#include "Managers/TagManager.hpp"
#include "Managers/TeamManager.hpp"
#include "Systems/DelayedEntityProcessingSystem.hpp"
#include "Systems/EntityProcessingSystem.hpp"
#include "Systems/IntervalEntityProcessingSystem.hpp"
#include "Systems/IntervalEntitySystem.hpp"
#include "Systems/VoidEntitySystem.hpp"
