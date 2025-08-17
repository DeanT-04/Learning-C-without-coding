#!/usr/bin/env python3
"""
C Programming Lessons Progress Report Generator
Generates comprehensive progress reports and learning analytics
"""

import os
import json
import datetime
from pathlib import Path
from typing import Dict, List, Tuple

class ProgressReportGenerator:
    def __init__(self):
        self.config = self._load_config()
        self.progress_data = {}
        
    def _load_config(self) -> Dict:
        """Load test configuration"""
        try:
            with open('test_config.json', 'r') as f:
                return json.load(f)
        except FileNotFoundError:
            return self._get_default_config()
    
    def _get_default_config(self) -> Dict:
        """Return default configuration if config file not found"""
        return {
            "test_configuration": {
                "difficulty_levels": {
                    "basics": {"expected_lessons": 6, "topics": []},
                    "intermediate": {"expected_lessons": 6, "topics": []},
                    "pro": {"expected_lessons": 6, "topics": []},
                    "master": {"expected_lessons": 6, "topics": []}
                }
            }
        }
    
    def generate_comprehensive_report(self):
        """Generate comprehensive progress report"""
        print("=" * 60)
        print("C PROGRAMMING LESSONS - COMPREHENSIVE PROGRESS REPORT")
        print("=" * 60)
        print(f"Generated: {datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print()
        
        # Overall project statistics
        self._generate_project_overview()
        
        # Difficulty level analysis
        self._analyze_difficulty_levels()
        
        # Lesson completion status
        self._analyze_lesson_completion()
        
        # Code quality metrics
        self._analyze_code_quality()
        
        # Learning path recommendations
        self._generate_recommendations()
        
        # Export data for external analysis
        self._export_progress_data()
    
    def _generate_project_overview(self):
        """Generate overall project statistics"""
        print("📊 PROJECT OVERVIEW")
        print("-" * 30)
        
        total_lessons = 0
        completed_lessons = 0
        total_files = 0
        
        difficulty_levels = self.config["test_configuration"]["difficulty_levels"]
        
        for level_name, level_config in difficulty_levels.items():
            level_path = Path(level_name)
            if level_path.exists():
                lessons = list(level_path.glob('lesson-*'))
                total_lessons += len(lessons)
                
                for lesson in lessons:
                    if self._is_lesson_complete(lesson):
                        completed_lessons += 1
                    
                    # Count files in lesson
                    total_files += len(list(lesson.glob('*')))
        
        completion_rate = (completed_lessons / total_lessons * 100) if total_lessons > 0 else 0
        
        print(f"Total Lessons: {total_lessons}")
        print(f"Completed Lessons: {completed_lessons}")
        print(f"Completion Rate: {completion_rate:.1f}%")
        print(f"Total Files: {total_files}")
        print()
        
        # Store for export
        self.progress_data['overview'] = {
            'total_lessons': total_lessons,
            'completed_lessons': completed_lessons,
            'completion_rate': completion_rate,
            'total_files': total_files
        }
    
    def _analyze_difficulty_levels(self):
        """Analyze progress by difficulty level"""
        print("📈 DIFFICULTY LEVEL ANALYSIS")
        print("-" * 35)
        
        difficulty_levels = self.config["test_configuration"]["difficulty_levels"]
        level_progress = {}
        
        for level_name, level_config in difficulty_levels.items():
            level_path = Path(level_name)
            
            if not level_path.exists():
                print(f"{level_name.upper()}: ❌ Directory not found")
                continue
            
            lessons = sorted(level_path.glob('lesson-*'))
            expected = level_config.get("expected_lessons", 0)
            completed = sum(1 for lesson in lessons if self._is_lesson_complete(lesson))
            
            completion_rate = (completed / len(lessons) * 100) if lessons else 0
            
            status_icon = "✅" if completed == len(lessons) else "🔄" if completed > 0 else "⏳"
            
            print(f"{level_name.upper()}: {status_icon} {completed}/{len(lessons)} lessons ({completion_rate:.1f}%)")
            
            if len(lessons) != expected:
                print(f"  ⚠️  Expected {expected} lessons, found {len(lessons)}")
            
            level_progress[level_name] = {
                'completed': completed,
                'total': len(lessons),
                'expected': expected,
                'completion_rate': completion_rate
            }
        
        print()
        self.progress_data['difficulty_levels'] = level_progress
    
    def _analyze_lesson_completion(self):
        """Analyze individual lesson completion status"""
        print("📋 LESSON COMPLETION STATUS")
        print("-" * 35)
        
        difficulty_levels = self.config["test_configuration"]["difficulty_levels"]
        lesson_details = {}
        
        for level_name in difficulty_levels.keys():
            level_path = Path(level_name)
            if not level_path.exists():
                continue
            
            print(f"\n{level_name.upper()} Level:")
            lessons = sorted(level_path.glob('lesson-*'))
            level_lessons = []
            
            for lesson in lessons:
                is_complete = self._is_lesson_complete(lesson)
                has_executable = self._has_executable(lesson)
                file_count = len(list(lesson.glob('*')))
                
                status_icon = "✅" if is_complete else "❌"
                exec_icon = "🔧" if has_executable else "⚪"
                
                print(f"  {status_icon} {exec_icon} {lesson.name} ({file_count} files)")
                
                level_lessons.append({
                    'name': lesson.name,
                    'complete': is_complete,
                    'has_executable': has_executable,
                    'file_count': file_count
                })
            
            lesson_details[level_name] = level_lessons
        
        print()
        self.progress_data['lesson_details'] = lesson_details
    
    def _analyze_code_quality(self):
        """Analyze code quality metrics"""
        print("🔍 CODE QUALITY ANALYSIS")
        print("-" * 30)
        
        total_c_files = 0
        total_lines = 0
        files_with_comments = 0
        files_with_proper_headers = 0
        
        for level_dir in ['basics', 'intermediate', 'pro', 'master']:
            level_path = Path(level_dir)
            if not level_path.exists():
                continue
            
            for c_file in level_path.rglob('*.c'):
                total_c_files += 1
                
                try:
                    with open(c_file, 'r', encoding='utf-8') as f:
                        content = f.read()
                        lines = content.split('\n')
                        total_lines += len(lines)
                        
                        # Check for comments
                        if '//' in content or '/*' in content:
                            files_with_comments += 1
                        
                        # Check for proper headers
                        if '#include' in content:
                            files_with_proper_headers += 1
                            
                except Exception:
                    continue
        
        if total_c_files > 0:
            avg_lines_per_file = total_lines / total_c_files
            comment_rate = files_with_comments / total_c_files * 100
            header_rate = files_with_proper_headers / total_c_files * 100
            
            print(f"Total C Files: {total_c_files}")
            print(f"Total Lines of Code: {total_lines}")
            print(f"Average Lines per File: {avg_lines_per_file:.1f}")
            print(f"Files with Comments: {comment_rate:.1f}%")
            print(f"Files with Headers: {header_rate:.1f}%")
        else:
            print("No C files found for analysis")
        
        print()
        
        self.progress_data['code_quality'] = {
            'total_c_files': total_c_files,
            'total_lines': total_lines,
            'avg_lines_per_file': total_lines / total_c_files if total_c_files > 0 else 0,
            'comment_rate': files_with_comments / total_c_files * 100 if total_c_files > 0 else 0,
            'header_rate': files_with_proper_headers / total_c_files * 100 if total_c_files > 0 else 0
        }
    
    def _generate_recommendations(self):
        """Generate learning path recommendations"""
        print("💡 LEARNING RECOMMENDATIONS")
        print("-" * 35)
        
        # Analyze current progress to make recommendations
        difficulty_levels = ['basics', 'intermediate', 'pro', 'master']
        current_level = None
        
        for level in difficulty_levels:
            level_path = Path(level)
            if level_path.exists():
                lessons = list(level_path.glob('lesson-*'))
                completed = sum(1 for lesson in lessons if self._is_lesson_complete(lesson))
                
                if completed < len(lessons):
                    current_level = level
                    break
        
        if current_level:
            print(f"🎯 Focus on: {current_level.upper()} level")
            print(f"   Continue with incomplete lessons in {current_level}/")
        else:
            print("🎉 All lessons completed! Consider:")
            print("   - Building personal projects")
            print("   - Contributing to open source")
            print("   - Learning advanced topics")
        
        print("\n📚 General Recommendations:")
        print("   - Practice coding daily")
        print("   - Experiment with code modifications")
        print("   - Build projects using learned concepts")
        print("   - Review and refactor previous code")
        
        print()
    
    def _export_progress_data(self):
        """Export progress data to JSON file"""
        output_file = f"progress_report_{datetime.datetime.now().strftime('%Y%m%d_%H%M%S')}.json"
        
        export_data = {
            'generated_at': datetime.datetime.now().isoformat(),
            'progress_data': self.progress_data
        }
        
        try:
            with open(output_file, 'w') as f:
                json.dump(export_data, f, indent=2)
            print(f"📄 Progress data exported to: {output_file}")
        except Exception as e:
            print(f"❌ Failed to export progress data: {e}")
        
        print()
    
    def _is_lesson_complete(self, lesson_path: Path) -> bool:
        """Check if a lesson is complete"""
        required_files = ['main.c', 'Makefile', 'README.md']
        return all((lesson_path / file).exists() for file in required_files)
    
    def _has_executable(self, lesson_path: Path) -> bool:
        """Check if lesson has compiled executable"""
        return any(lesson_path.glob('*.exe')) or any(lesson_path.glob('*.out'))

def main():
    """Main function"""
    generator = ProgressReportGenerator()
    generator.generate_comprehensive_report()

if __name__ == "__main__":
    main()