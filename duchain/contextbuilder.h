/* This file is part of KDevelop
    Copyright 2006 Roberto Raggi <roberto@kdevelop.org>
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

#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include "parser/javadefaultvisitor.h"

#include <language/duchain/builders/abstractcontextbuilder.h>

#include "classdeclaration.h"

class JavaLanguageSupport;

namespace java {

class EditorIntegrator;
class IdentifierCompiler;
class ParseSession;

typedef KDevelop::AbstractContextBuilder<AstNode, IdentifierAst> ContextBuilderBase;

/**
 * A class which iterates the AST to identify contexts.
 */
class ContextBuilder: public ContextBuilderBase, protected DefaultVisitor
{
public:
  ContextBuilder();
  virtual ~ContextBuilder ();

  void setEditor(EditorIntegrator* editor);
  void setEditor(ParseSession* session);

  void setJavaSupport(JavaLanguageSupport* java);

protected:
  EditorIntegrator* editor() const;

  virtual KDevelop::TopDUContext* newTopContext(const KDevelop::SimpleRange& range, KDevelop::ParsingEnvironmentFile* file = 0);
  virtual KDevelop::DUContext* newContext(const KDevelop::SimpleRange& range);

  virtual void startVisiting( AstNode* node );
  virtual void setContextOnNode( AstNode* node, KDevelop::DUContext* ctx );
  virtual KDevelop::DUContext* contextFromNode( AstNode* node );
  virtual KTextEditor::Range editorFindRange( AstNode* fromRange, AstNode* toRange );

  /**
   * Compile an identifier for the specified AstNode \a id.
   *
   * \note this reference will only be valid until the next time the function
   * is called, so you need to create a copy (store as non-reference).
   * @param typeSpecifier a pointer that will eventually be filled with a type-specifier that can be found in the name(for example the return-type of a cast-operator)
   */
  virtual KDevelop::QualifiedIdentifier identifierForNode(IdentifierAst* id);
  KDevelop::QualifiedIdentifier identifierForNode(QualifiedIdentifierAst* id);
  KDevelop::QualifiedIdentifier identifierForNode(const KDevPG::ListNode<IdentifierAst*>* id);

  // Visitors
  template<typename T>
  void visitNodeList(const KDevPG::ListNode<T*>* list)
  {
    if (list) {
      const KDevPG::ListNode<T*> *__it = list->front(), *__end = __it;
      do
      {
          visitNode(__it->element);
          __it = __it->next;
      }
      while (__it != __end);
    }
  }

  virtual void visitCompilationUnit(java::CompilationUnitAst* node);
  virtual void visitForStatement(ForStatementAst *node);
  virtual void visitIfStatement(IfStatementAst *node);
  virtual void visitClassDeclaration(ClassDeclarationAst *node);
  virtual void visitMethodDeclaration(MethodDeclarationAst *node);
  virtual void visitConstructorDeclaration(ConstructorDeclarationAst *node);
  virtual void visitInterfaceDeclaration(InterfaceDeclarationAst *node);
  virtual void visitEnumDeclaration(java::EnumDeclarationAst* node);

  virtual void addBaseType( BaseClassInstance base );

protected:
  virtual void classContextOpened(KDevelop::DUContext* context);

  // Variables
  IdentifierCompiler* m_identifierCompiler;

private:
  JavaLanguageSupport* m_java;
};

}

#endif // CONTEXTBUILDER_H

