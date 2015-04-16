#include "zealsearchplugin.h"
#include "zealsearch_config.h"
#include "zealsearchview.h"

#include <KTextEditor/Document>
#include <KTextEditor/View>

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>
#include <KConfigGroup>

#include <QProcess>
#include <QString>
#include <QFileInfo>
#include <QMap>
#include <QStringList>

ZealSearchPlugin *ZealSearchPlugin::plugin = 0;

K_PLUGIN_FACTORY_DEFINITION(ZealSearchPluginFactory, 
		 registerPlugin<ZealSearchPlugin>("ktexteditor_zealsearch");
		 registerPlugin<ZealSearch_config>("ktexteditor_zealsearch_config");
		)
K_EXPORT_PLUGIN(ZealSearchPluginFactory("ktexteditor_zealsearch", "ktexteditor_plugins"))

ZealSearchPlugin::ZealSearchPlugin(QObject *parent, const QVariantList &args)
: KTextEditor::Plugin(parent)
{
  Q_UNUSED(args);
  plugin = this;
  readConfig();
}

ZealSearchPlugin::~ZealSearchPlugin()
{
  plugin = 0;
}

void ZealSearchPlugin::addView(KTextEditor::View *view)
{
	ZealSearchView *nview = new ZealSearchView(view, zealCmd, docSets);
	m_views.append(nview);
}

void ZealSearchPlugin::removeView(KTextEditor::View *view)
{
	for(int z = 0; z < m_views.size(); z++)
	{
		if(m_views.at(z)->parentClient() == view)
		{
			ZealSearchView *nview = m_views.at(z);
			m_views.removeAll(nview);
			delete nview;
		}
	}
}
void ZealSearchPlugin::setDocSetsStr(QString docSets_str)
{
  docSets.clear();
  QStringList docSets_list = docSets_str.split("\n", QString::SkipEmptyParts);
  QStringListIterator dli(docSets_list);
  while (dli.hasNext()){
    QString i = dli.next();
    QStringList p = i.split(":");
    if(p.size() == 2){
      docSets[p.at(0)] = p.at(1);
    }
  }
}

QString ZealSearchPlugin::getDocSetsStr()
{
  QStringList docSets_list;
  QMapIterator<QString, QString> dsi(docSets);
  while (dsi.hasNext()) {
    dsi.next();
    docSets_list << dsi.key() + ':' + dsi.value();
  }
  QString docSets_str = docSets_list.join("\n");
  return docSets_str;
}

void ZealSearchPlugin::readConfig()
{
  KConfigGroup cg(KGlobal::config(), "ZealSearch Plugin");
  zealCmd = cg.readEntry("zeal_command", "/usr/bin/zeal --query \"%1\"");
  QString docSets_str = cg.readEntry("zeal_docsets", "php:html,joomla,php,wordpress\nhtml:html\ncss:css,less\njs:javascript,jquery\n");
  setDocSetsStr(docSets_str);
}

void ZealSearchPlugin::writeConfig()
{
  KConfigGroup cg(KGlobal::config(), "ZealSearch Plugin");
  cg.writeEntry("zeal_command", zealCmd);
  cg.writeEntry("zeal_docsets", getDocSetsStr());
}

ZealSearchView::ZealSearchView(KTextEditor::View *view, const QString& zealCmd, const QMap<QString, QString>& docSets)
: QObject(view)
, KXMLGUIClient(view)
, m_view(view)
, m_zealCmd(zealCmd)
, m_docSets(docSets)
{
	setComponentData(ZealSearchPluginFactory::componentData());
	
	KConfigGroup cg(KGlobal::config(), "ZealSearch Plugin");
	
	KAction *action = new KAction(i18n("ZealSearch"), this);
	actionCollection()->addAction("tools_zealsearch", action);
	//action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
	connect(action, SIGNAL(triggered()), this, SLOT(insertZealSearch()));
	
	setXMLFile("zealsearchui.rc");
}

ZealSearchView::~ZealSearchView()
{
}

void ZealSearchView::insertZealSearch()
{
  QFileInfo fi(m_view->document()->documentName());
  QString docExt = fi.suffix();
  QString searchTerm = m_view->selectionText();
  if(!m_docSets[docExt].isEmpty())
    searchTerm = m_docSets[docExt] + ':' + searchTerm;

  QProcess myProcess;
  myProcess.startDetached(m_zealCmd.arg(searchTerm));
}

#include "zealsearchview.moc"
