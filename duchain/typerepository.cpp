/* This file is part of KDevelop
    Copyright 2006-2008 Hamish Rodda <rodda@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "typerepository.h"

#include <QMutexLocker>

#include <kglobal.h>
#include <duchain/identifier.h>

using namespace KDevelop;
using namespace java;

TypeRepository::TypeRepository()
{
  m_integrals.reserve(18 * 4);

  // void - 0
  newIntegralType(IntegralType::TypeVoid);

  // bool - 1
  newIntegralType(IntegralType::TypeBoolean);

  // char - 2
  newIntegralType(IntegralType::TypeChar);

  // byte - 3
  newIntegralType(IntegralType::TypeByte);

  // int - 4
  newIntegralType(IntegralType::TypeInt);

  // short - 5
  newIntegralType(IntegralType::TypeShort);

  // long - 6
  newIntegralType(IntegralType::TypeLong);

  // float - 7
  newIntegralType(IntegralType::TypeFloat);

  // double - 8
  newIntegralType(IntegralType::TypeDouble);

  // null - 9
  newIntegralType(IntegralType::TypeNull);
}

java::IntegralType::Ptr TypeRepository::integral(IntegralType::IntegralTypes type) const
{
  switch (type) {
    case IntegralType::TypeVoid:
      return getIntegral(0);

    case IntegralType::TypeBoolean:
      return getIntegral(1);

    case IntegralType::TypeChar:
      return getIntegral(2);

    case IntegralType::TypeByte:
      return getIntegral(3);

    case IntegralType::TypeInt:
      return getIntegral(4);

    case IntegralType::TypeShort:
      return getIntegral(5);

    case IntegralType::TypeLong:
      return getIntegral(6);

    case IntegralType::TypeFloat:
      return getIntegral(7);

    case IntegralType::TypeDouble:
        return getIntegral(8);

    case IntegralType::TypeNull:
        return getIntegral(9);

    default:
      break;
  }

  return IntegralType::Ptr();
}

void TypeRepository::newIntegralType(IntegralType::IntegralTypes type)
{
  IntegralType* plainType = new IntegralType(type);

  /*IntegralType* constVersion = new IntegralType(type, modifiers);
  constVersion->setConstant(true);

  IntegralType* volatileVersion = new IntegralType(type, modifiers);
  volatileVersion->setVolatile(true);

  IntegralType* constVolatileVersion = new IntegralType(type, modifiers);
  constVolatileVersion->setVolatile(true);
  constVolatileVersion->setConstant(true);*/

  m_integrals.append(IntegralType::Ptr(plainType));
  //m_integrals.append(IntegralType::Ptr(constVersion));
  //m_integrals.append(IntegralType::Ptr(volatileVersion));
  //m_integrals.append(IntegralType::Ptr(constVolatileVersion));
}

TypeRepository* TypeRepository::self()
{
  K_GLOBAL_STATIC(TypeRepository, s_instance)
  return s_instance;
}

java::IntegralType::Ptr TypeRepository::getIntegral(int index) const
{
  return m_integrals.at(index);
}

AbstractType::Ptr TypeRepository::registerType(AbstractType::Ptr input)
{
  if (!input) {
    kWarning() << "Asked to register a null type." ;
    return input;
  }

  switch (input->whichType()) {
    case AbstractType::TypeAbstract:
      return input;

    case AbstractType::TypeIntegral:
      return input;

    case AbstractType::TypePointer:
      return registerPointer(PointerType::Ptr::dynamicCast(input));

    case AbstractType::TypeReference:
      return registerReference(ReferenceType::Ptr::dynamicCast(input));

    case AbstractType::TypeFunction:
      return registerFunction(FunctionType::Ptr::dynamicCast(input));

    case AbstractType::TypeStructure:
      return input;

    case AbstractType::TypeArray:
      return registerArray(ArrayType::Ptr::dynamicCast(input));

    default:
      return input;
  }
}

AbstractType::Ptr TypeRepository::registerPointer(PointerType::Ptr input)
{
  QMutexLocker lock(&m_mutex);

  Q_ASSERT(input);

  if (!input->baseType())
    // Invalid
    return AbstractType::Ptr::staticCast(input);

  TypeModifiers mod = input->modifiers();

  if (m_pointers.contains(input->baseType())) {
    QMultiHash<AbstractType::Ptr, PointerType::Ptr>::ConstIterator it(m_pointers.constFind(input->baseType()));
    if (it != m_pointers.constEnd())
      for (; it.key() == input->baseType(); ++it)
        if (it.value()->modifiers() == mod)
          // Match
          return AbstractType::Ptr::staticCast(it.value());
  }

  // No match
  m_pointers.insert(input->baseType(), input);
  return AbstractType::Ptr::staticCast(input);
}

AbstractType::Ptr TypeRepository::registerReference(ReferenceType::Ptr input)
{
  QMutexLocker lock(&m_mutex);

  Q_ASSERT(input);

  if (!input->baseType())
    // Invalid
    return AbstractType::Ptr::staticCast(input);

  TypeModifiers mod = input->modifiers();

  if (m_references.contains(input->baseType())) {
    QMultiHash<AbstractType::Ptr, ReferenceType::Ptr>::ConstIterator it = m_references.constFind(input->baseType());
    if (it != m_references.constEnd())
      for (; it.key() == input->baseType(); ++it)
        if (it.value()->modifiers() == mod)
          // Match
          return AbstractType::Ptr::staticCast(it.value());
  }

  // No match
  m_references.insert(input->baseType(), input);
  return AbstractType::Ptr::staticCast(input);
}

int hashFromFunction(java::FunctionType* function) {
  int ret = 1;
  const int numElements = function->arguments().count();
  for (int i = 0; i < numElements; ++i)
    ret = (int)((size_t)function->arguments()[i].data()) + ret*13;
  ret = (int)((size_t)function) + ret * 37;
  ret = (int)((size_t)function->modifiers()) + ret * 17;
  return ret;

}

AbstractType::Ptr TypeRepository::registerFunction(FunctionType::Ptr input)
{
  QMutexLocker lock(&m_mutex);

  Q_ASSERT(input);

  AbstractType* returnType = input->returnType().data();
  const int numElements = input->arguments().count();
  if (!returnType)
    // Invalid
    return AbstractType::Ptr::staticCast(input);

  foreach (const AbstractType::Ptr& argument, input->arguments())
    if (!argument)
      // Invalid
      return AbstractType::Ptr::staticCast(input);

  int hash = hashFromFunction(input.data());

  TypeModifiers mod = input->modifiers();

  QMultiHash<int, FunctionType::Ptr>::ConstIterator it = m_functions.constFind(hash);
  if (it != m_functions.constEnd()) {
    for (; it.key() == hash; ++it) {
      if(numElements != (*it)->arguments().count())
        continue;
      if (it.value()->modifiers() == mod) {
        if (it.value()->returnType() != returnType)
          goto nomatch;

        for (int i = 0; i < numElements; ++i)
          if (it.value()->arguments()[i] != input->arguments()[i])
            goto nomatch;

        // Match
        return AbstractType::Ptr::staticCast(it.value());
      }
      nomatch:
      continue;
    }
  }

  // No match
  m_functions.insert(hash, input);
  return AbstractType::Ptr::staticCast(input);
}


AbstractType::Ptr TypeRepository::registerArray(ArrayType::Ptr input)
{
  QMutexLocker lock(&m_mutex);

  Q_ASSERT(input);

  if (!input->elementType())
    // Invalid
    return AbstractType::Ptr::staticCast(input);

  if (m_arrays.contains(input->elementType())) {
    QMultiHash<AbstractType::Ptr, ArrayType::Ptr>::ConstIterator it = m_arrays.constFind(input->elementType());
    if (it != m_arrays.constEnd())
      for (; it.key() == input->elementType(); ++it)
        // Match
        return AbstractType::Ptr::staticCast(it.value());
  }

  // No match
  m_arrays.insert(input->elementType(), input);
  return AbstractType::Ptr::staticCast(input);
}
