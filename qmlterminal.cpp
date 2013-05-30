#include "qmlterminal.h"

QMLTerminal::QMLTerminal(QQuickPaintedItem *parent):
    QQuickPaintedItem(parent),
    m_width(320),
    m_height(240)
{
    // What it can do
    setFlag(ItemHasContents, true);
    setFlag(ItemAcceptsInputMethod, true);
    setFlag(ItemIsFocusScope, true);

    // Update our 'painter' when the widget updates.
    connect( &m_terminal, SIGNAL(updated(QRect)), this, SLOT(update(QRect)) );
    connect( this, SIGNAL(sizeChanged()), this, SLOT(resized()) );
    connect( this, SIGNAL(heightChanged()), this, SLOT(resized()) );
    connect( this, SIGNAL(widthChanged()), this, SLOT(resized()) );
    connect( this, SIGNAL(implicitHeightChanged()), this, SLOT(resized()) );
    connect( this, SIGNAL(implicitWidthChanged()), this, SLOT(resized()) );
    connect( &m_terminal, SIGNAL(finished()), this, SIGNAL(finished()) );
    connect( this, SIGNAL(focusChanged(bool)), &m_terminal, SLOT(focus(bool)) );

    // Set colours
    setColours();

    // Focus initially.
    m_terminal.focus(true);

    // Popups baaaad
    m_terminal.setTerminalSizeHint(false);
}

void QMLTerminal::setColours()
{
    //ColorScheme scheme;

    //m_terminal.setColorScheme(scheme);
}

void QMLTerminal::resized()
{
    qDebug() << "Resizing to:" << this->width() << "x" << this->height();
    m_terminal.resize( this->width(), this->height() );
}

QMLTerminal::~QMLTerminal()
{
}

void QMLTerminal::update(const QRect &rect)
{
    QQuickPaintedItem::update(rect);
}

void QMLTerminal::paint(QPainter *painter)
{
    QRectF dest = contentsBoundingRect();
    QRegion region( dest.toRect() );
    m_terminal.render(painter, QPoint(), region);
}

void QMLTerminal::sendKey(int key, int modifiers, bool pressed, quint32 nativeScanCode, const QString &text)
{
    if( pressed )
    {
        QKeyEvent keyevent = QKeyEvent( QEvent::KeyPress, key, (Qt::KeyboardModifier)modifiers, text );
        m_terminal.sendKey( &keyevent );
        return;
    }

    QKeyEvent keyevent = QKeyEvent( QEvent::KeyRelease, key, (Qt::KeyboardModifier)modifiers, text );
    m_terminal.sendKey( &keyevent );
}
