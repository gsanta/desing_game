import PointerData from './PointerData';
import ToolType from './ToolType';

interface Tool {
  type: ToolType;
  onClick(pointer: PointerData): void;
}

export default Tool;
