#ifndef ZEALSEARCHVIEW_H
#define ZEALSEARCHVIEW_H

#include <QObject>
#include <KXMLGUIClient>

class ZealSearchView : public QObject, public KXMLGUIClient
{
	Q_OBJECT
	public:
		explicit ZealSearchView(KTextEditor::View *view, const QString& zealCmd, const QMap<QString, QString>& docSets);
		~ZealSearchView();
	private slots:
		void insertZealSearch();
	private:
		KTextEditor::View *m_view;
		const QString& m_zealCmd;
		const QMap<QString, QString>& m_docSets;
};

#endif
