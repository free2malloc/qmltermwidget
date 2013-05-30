#ifndef QMLTERMINAL_H
#define QMLTERMINAL_H

#include <QQuickPaintedItem>
#include <qtermwidget.h>

class QMLTerminal : public QQuickPaintedItem
{
    Q_OBJECT
    Q_DISABLE_COPY(QMLTerminal)

    QTermWidget m_terminal;

    typedef enum {
        /** Do not show the scroll bar. */
        NoScrollBar=0,
        /** Show the scroll bar on the left side of the display. */
        ScrollBarLeft=1,
        /** Show the scroll bar on the right side of the display. */
        ScrollBarRight=2
    } ScrollBarPosition;

    qreal m_width;
    qreal m_height;
    
    Q_PROPERTY(ScrollBarPosition scrollbarPosition READ getScrollBarPosition WRITE setScrollBarPosition NOTIFY scrollBarPositionChanged)
    Q_PROPERTY(QString keyBindings READ keyBindings WRITE setKeyBindings NOTIFY keyBindingsChanged)
    Q_PROPERTY(bool flowcontrol READ flowControlEnabled WRITE setFlowControlEnabled NOTIFY flowControlChanged)
    Q_PROPERTY(QFont font READ getTerminalFont WRITE setTerminalFont NOTIFY fontChanged)
    Q_PROPERTY(QStringList environment READ getEnvironment WRITE setEnvironment NOTIFY environmentChanged)
    Q_PROPERTY(QString shellProgram READ getShellProgram WRITE setShellProgram NOTIFY shellProgramChanged)
    Q_PROPERTY(QString workingDirectory READ getWorkingDirectory WRITE setWorkingDirectory NOTIFY workingDirectoryChanged)
    Q_PROPERTY(QStringList shellArguments READ getArgs WRITE setArgs NOTIFY argsChanged)
    Q_PROPERTY(QString textCodec READ getTextCodec WRITE setTextCodec NOTIFY textCodecChanged)
    Q_PROPERTY(QSize gridSize READ getGridSize WRITE setGridSize NOTIFY sizeChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY sizeChanged)
    Q_PROPERTY(int columns READ columns WRITE setColumns NOTIFY sizeChanged)
    Q_PROPERTY(int historySize READ getHistorySize WRITE setHistorySize NOTIFY historySizeChanged)

public:
    QMLTerminal(QQuickPaintedItem *parent = 0);
    ~QMLTerminal();

    Q_INVOKABLE QStringList availableColorSchemes() { return m_terminal.availableColorSchemes(); }
    Q_INVOKABLE void setColorScheme(const QString &name) { m_terminal.setColorScheme(name); }

    Q_INVOKABLE void setGridSize(QSize size) { m_terminal.setSize( size.width(), size.height() ); }
    Q_INVOKABLE QSize getGridSize() { return QSize( m_terminal.columns(), m_terminal.rows() ); }

    Q_INVOKABLE int rows() { return m_terminal.rows(); }
    Q_INVOKABLE int columns() { return m_terminal.columns(); }

    Q_INVOKABLE void setRows(int rows) { m_terminal.setSize( m_terminal.columns(), rows ); }
    Q_INVOKABLE void setColumns(int columns) { m_terminal.setSize( columns, m_terminal.rows() ); }

    void paint(QPainter *painter);

public slots:
    ScrollBarPosition getScrollBarPosition() { return (ScrollBarPosition)m_terminal.getScrollBarPosition(); }
    QString keyBindings() { return m_terminal.keyBindings(); }
    bool flowControlEnabled() { return m_terminal.flowControlEnabled(); }
    QFont getTerminalFont() { return m_terminal.getTerminalFont(); }
    QStringList getEnvironment() { return m_terminal.getEnvironment(); }
    QString getShellProgram() { return m_terminal.getShellProgram(); }
    QString getWorkingDirectory() { return m_terminal.getWorkingDirectory(); }
    QStringList getArgs() { return m_terminal.getArgs(); }
    QString getTextCodec() { return m_terminal.getTextCodec(); }
    int getHistorySize() { return m_terminal.getHistorySize(); }

    void setScrollBarPosition(ScrollBarPosition position) { m_terminal.setScrollBarPosition((QTermWidget::ScrollBarPosition)position); }
    void setKeyBindings(QString bindings) { m_terminal.setKeyBindings(bindings); }
    void setFlowControlEnabled(bool toggle) { m_terminal.setFlowControlEnabled(toggle); }
    void setTerminalFont(QFont font) { m_terminal.setTerminalFont(font); }
    void setEnvironment(QStringList values) { m_terminal.setEnvironment(values); }
    void setShellProgram(QString program) { m_terminal.setShellProgram(program); }
    void setWorkingDirectory(QString path) { m_terminal.setWorkingDirectory(path); }
    void setArgs(QStringList arguments) { m_terminal.setArgs(arguments); }
    void setTextCodec(QString codecName) { m_terminal.setTextCodec(codecName); }
    void setHistorySize(int lines) { m_terminal.setHistorySize(lines); }

    void setWidth(qreal w) { m_width = w; m_terminal.resize(m_width, m_height); }
    void setHeight(qreal h) { m_height = h; m_terminal.resize(m_width, m_height); }

    void sendKey(int key, int modifiers, bool pressed, quint32 nativeScanCode, const QString &text);
    void setColours();

protected slots:
    void update(const QRect &rect);
    void resized();

signals:
    void scrollBarPositionChanged();
    void keyBindingsChanged();
    void flowControlChanged();
    void fontChanged();
    void environmentChanged();
    void shellProgramChanged();
    void workingDirectoryChanged();
    void argsChanged();
    void textCodecChanged();
    void sizeChanged();
    void historySizeChanged();
    void finished();
};

QML_DECLARE_TYPE(QMLTerminal)

#endif // QMLTERMINAL_H

