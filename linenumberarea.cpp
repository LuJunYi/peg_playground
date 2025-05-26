#include "linenumberarea.h"
#include "codeeditor.h"
#include <QPaintEvent>

void LineNumberArea::paintEvent(QPaintEvent *event) {
    codeEditor->lineNumberAreaPaintEvent(event);
}